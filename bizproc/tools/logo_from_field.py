"""Переводит логотип в письмах БП на поле сотрудника (по аналогии с аватаркой).

Что делает с каждым шаблоном:
  * добавляет константу шаблона LogoUrl — прямая HTTPS-ссылка на PNG логотипа;
  * вместо безусловной записи логотипа ставит условие: если поле сотрудника
    UF_USR_1790366508950 пустое — записать в него LogoUrl через n8n Bridge
    (user.update) и выдержать паузу, как в ветке аватарки;
  * во всех письмах <img> логотипа берёт src из поля
    {=Document:ASSIGNED_BY.UF_USR_1790366508950}.

Запуск: python3 logo_from_field.py <in.bpt> <out.bpt> [<in.bpt> <out.bpt> ...]
"""
import base64
import copy
import re
import sys

from phps import PArr, load_bpt, save_bpt

LOGO_FIELD = 'UF_USR_1790366508950'
LOGO_REF = '{=Document:ASSIGNED_BY.%s}' % LOGO_FIELD
LOGO_CONST = 'LogoUrl'
LOGO_DEFAULT = 'https://n8n.plus-tech.ru/email-assets/kazna-logo.png'

AVATAR_WRITE = b'A55000_55000_55000_55002'
AVATAR_PAUSE = b'A33985_13173_18297_48562'
AVATAR_IF = b'A55000_55000_55000_55009'
OLD_LOGO_WRITES = {b'A45800_45800_45800_45810', b'A55200_55200_55200_55210'}

LOGO_IF = b'A45800_45800_45800_45809'
LOGO_FILLED = b'A45800_45800_45800_45811'
LOGO_EMPTY = b'A45800_45800_45800_45812'
LOGO_WRITE = b'A45800_45800_45800_45810'
LOGO_PAUSE = b'A45800_45800_45800_45813'

LOGO_IMG = (
    '<img src="%s" class="supplied-logo" width="205" height="69" '
    'alt="Казначейство Онлайн" style="display:block; width:205px; max-width:100%%; '
    'height:auto; border:0; outline:none;">' % LOGO_REF
)
LOGO_IMG_RE = re.compile(r'<img\b[^>]*\bclass="(?:supplied-logo|brand-logo)"[^>]*>')


def u(text):
    return text.encode('utf-8')


def children(act):
    return act.get(b'Children') or PArr()


def iter_acts(act):
    yield act
    for _, ch in children(act):
        yield from iter_acts(ch)


def find(root, name):
    for act in iter_acts(root):
        if act.get(b'Name') == name:
            return act
    raise KeyError(name)


def reindex(items):
    return PArr((i, v) for i, (_, v) in enumerate(items))


def make_logo_block(root):
    write = copy.deepcopy(find(root, AVATAR_WRITE))
    write.set(b'Name', LOGO_WRITE)
    props = write.get(b'Properties')
    props.set(b'PARAMS', u('{"ID":"{=Document:ASSIGNED_BY_ID}","%s":"%s"}' % (LOGO_FIELD, LOGO_DEFAULT)))
    props.set(b'Title', u('Записать логотип в профиль сотрудника'))
    props.set(b'EditorComment', u('Записывает в %s ссылку из константы шаблона «Ссылка на логотип».' % LOGO_FIELD))

    pause = copy.deepcopy(find(root, AVATAR_PAUSE))
    pause.set(b'Name', LOGO_PAUSE)

    def branch(name, title, comment, cond, acts):
        return PArr([
            (b'Type', b'IfElseBranchActivity'),
            (b'Name', name),
            (b'Activated', b'Y'),
            (b'Node', None),
            (b'Properties', PArr([(b'Title', u(title)), (b'EditorComment', u(comment))] + cond)),
            (b'Children', reindex([(0, a) for a in acts])),
        ])

    filled = branch(
        LOGO_FILLED, 'Ссылка на логотип уже заполнена',
        'Повторно не записываем, если ссылка на логотип уже сохранена в профиле.',
        [(b'fieldcondition', PArr([(0, PArr([(0, u('ASSIGNED_BY.' + LOGO_FIELD)), (1, b'!empty'), (2, b''), (3, b'0')]))]))],
        [],
    )
    empty = branch(
        LOGO_EMPTY, 'Ссылка на логотип не заполнена',
        'Записываем ссылку на логотип из константы шаблона один раз и сохраняем в профиль.',
        [(b'truecondition', b'1')],
        [write, pause],
    )
    return PArr([
        (b'Type', b'IfElseActivity'),
        (b'Name', LOGO_IF),
        (b'Activated', b'Y'),
        (b'Node', None),
        (b'Properties', PArr([
            (b'Title', u('Проверить сохраненную ссылку на логотип')),
            (b'EditorComment', u('Логотип заполняется по условию, как аватар: письма берут его из %s.' % LOGO_FIELD)),
            (b'_DesMinimized', b'N'),
        ])),
        (b'Children', PArr([(0, filled), (1, empty)])),
    ])


def replace_logo_write(root):
    """Заменяет безусловную запись логотипа на блок с условием (на том же месте)."""
    block = make_logo_block(root)
    for act in iter_acts(root):
        kids = children(act)
        for i, (k, ch) in enumerate(kids):
            if ch.get(b'Name') in OLD_LOGO_WRITES:
                kids[i] = (k, block)
                return
    raise RuntimeError('шаг записи логотипа не найден')


def patch_emails(root):
    count = 0
    for act in iter_acts(root):
        if act.get(b'Type') != b'CrmSendEmailActivity':
            continue
        props = act.get(b'Properties')
        text = props.get(b'MessageText')
        encoded = text.startswith(b'base64,')
        html = (base64.b64decode(text[7:]) if encoded else text).decode('utf-8')
        html, n = LOGO_IMG_RE.subn(LOGO_IMG, html)
        if n != 1:
            raise RuntimeError('%s: найдено %d <img> логотипа' % (act.get(b'Name'), n))
        data = html.encode('utf-8')
        props.set(b'MessageText', b'base64,' + base64.b64encode(data) if encoded else data)
        count += 1
    return count


def add_constant(tree):
    consts = tree.get(b'CONSTANTS')
    consts.set(u(LOGO_CONST), PArr([
        (b'Name', u('Ссылка на логотип')),
        (b'Description', u('Прямая HTTPS-ссылка на PNG. Записывается в поле сотрудника '
                           '«ссылка на лого компании», если оно пустое.')),
        (b'Type', b'string'),
        (b'Required', b'1'),
        (b'Multiple', b'0'),
        (b'Options', b''),
        (b'Default', u(LOGO_DEFAULT)),
    ]))


def fix_avatar_comment(root):
    props = find(root, AVATAR_IF).get(b'Properties')
    props.set(b'EditorComment', u('Аватар заполняется по условию; логотип — таким же отдельным условием.'))


def convert(src, dst):
    tree = load_bpt(src)
    (_, root), = tree.get(b'TEMPLATE')
    replace_logo_write(root)
    fix_avatar_comment(root)
    emails = patch_emails(root)
    names = [a.get(b'Name') for a in iter_acts(root)]
    assert len(names) == len(set(names)), 'дубли имён активностей'
    save_bpt(tree, dst)
    print('%s -> %s: писем обновлено %d' % (src, dst, emails))


if __name__ == '__main__':
    args = sys.argv[1:]
    if not args or len(args) % 2:
        sys.exit(__doc__)
    for i in range(0, len(args), 2):
        convert(args[i], args[i + 1])
