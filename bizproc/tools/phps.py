"""Order-preserving php serialize parser/serializer.
Arrays -> PArr (list of (key, value) pairs). Strings -> bytes. ints -> int, N -> None, b -> bool, d -> float(str kept)."""
import zlib


class PArr(list):
    def get(self, k, default=None):
        for kk, v in self:
            if kk == k:
                return v
        return default

    def set(self, k, val):
        for i, (kk, v) in enumerate(self):
            if kk == k:
                self[i] = (kk, val)
                return
        self.append((k, val))

    def keys(self):
        return [k for k, _ in self]


class PDouble:
    def __init__(self, raw):
        self.raw = raw


class PObj:
    def __init__(self, cls, arr):
        self.cls = cls
        self.arr = arr


def loads(data: bytes):
    pos = 0

    def parse():
        nonlocal pos
        t = data[pos:pos + 1]
        if t == b'N':
            assert data[pos + 1:pos + 2] == b';'
            pos += 2
            return None
        if t == b'i':
            end = data.index(b';', pos)
            v = int(data[pos + 2:end])
            pos = end + 1
            return v
        if t == b'd':
            end = data.index(b';', pos)
            v = PDouble(data[pos + 2:end])
            pos = end + 1
            return v
        if t == b'b':
            end = data.index(b';', pos)
            v = data[pos + 2:end] == b'1'
            pos = end + 1
            return v
        if t == b's':
            colon = data.index(b':', pos + 2)
            n = int(data[pos + 2:colon])
            assert data[colon + 1:colon + 2] == b'"'
            s = data[colon + 2:colon + 2 + n]
            assert data[colon + 2 + n:colon + 4 + n] == b'";', (pos, data[colon + 2 + n:colon + 10 + n])
            pos = colon + 4 + n
            return s
        if t == b'a':
            colon = data.index(b':', pos + 2)
            n = int(data[pos + 2:colon])
            assert data[colon + 1:colon + 2] == b'{'
            pos = colon + 2
            arr = PArr()
            for _ in range(n):
                k = parse()
                v = parse()
                arr.append((k, v))
            assert data[pos:pos + 1] == b'}', (pos, data[pos:pos + 20])
            pos += 1
            return arr
        if t == b'O':
            colon = data.index(b':', pos + 2)
            n = int(data[pos + 2:colon])
            cls = data[colon + 2:colon + 2 + n]
            pos = colon + 2 + n + 2  # skip '":'
            colon = data.index(b':', pos)
            cnt = int(data[pos:colon])
            pos = colon + 2
            arr = PArr()
            for _ in range(cnt):
                k = parse()
                v = parse()
                arr.append((k, v))
            assert data[pos:pos + 1] == b'}'
            pos += 1
            return PObj(cls, arr)
        raise ValueError('bad type %r at %d' % (t, pos))

    v = parse()
    assert pos == len(data), (pos, len(data))
    return v


def dumps(v) -> bytes:
    if v is None:
        return b'N;'
    if isinstance(v, bool):
        return b'b:1;' if v else b'b:0;'
    if isinstance(v, int):
        return b'i:%d;' % v
    if isinstance(v, PDouble):
        return b'd:' + v.raw + b';'
    if isinstance(v, str):
        v = v.encode('utf-8')
    if isinstance(v, (bytes, bytearray)):
        return b's:%d:"' % len(v) + bytes(v) + b'";'
    if isinstance(v, PObj):
        return (b'O:%d:"' % len(v.cls) + v.cls + b'":%d:{' % len(v.arr)
                + b''.join(dumps(k) + dumps(x) for k, x in v.arr) + b'}')
    if isinstance(v, list):
        return b'a:%d:{' % len(v) + b''.join(dumps(k) + dumps(x) for k, x in v) + b'}'
    raise TypeError(type(v))


def load_bpt(path):
    return loads(zlib.decompress(open(path, 'rb').read()))


def save_bpt(tree, path):
    data = dumps(tree)
    loads(data)  # validate
    open(path, 'wb').write(zlib.compress(data, 6))
    return data


def s(x):
    if isinstance(x, (bytes, bytearray)):
        return x.decode('utf-8', 'replace')
    return x
