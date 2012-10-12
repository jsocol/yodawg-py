try:
    from yodawg._dawg import Dawg
except ImportError:
    Dawg = None


VERSION = (0, 1, 0)
__version__ = '.'.join(str(i) for i in VERSION)
__all__ = ['Dawg']
