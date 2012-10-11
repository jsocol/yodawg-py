#include <Python.h>

#include "yodawg.h"

#define Dawg_Check(v) ((v)->ob_type == &dawg_Type)


typedef struct {
    PyObject_HEAD
    struct yonode *dawg;
} dawg;


void dawg_dealloc(PyObject *self);
int dawg_print(PyObject *self, FILE *fp, int flags);
PyObject *dawg_repr(PyObject *self);

PyTypeObject dawg_Type = {
    PyObject_HEAD_INIT(&PyType_Type)
    0,
    "dawg",  /* char *tp_name */
    sizeof(dawg),  /* int tp_basicsize */
    0,  /* int tp_itemsize - rarely used */
    dawg_dealloc,  /* destructor tp_dealloc */
    dawg_print,  /* printfunc tp_print */
    NULL,  /* getattrfunc tp_getattr - __getattr__ */
    NULL,  /* setattrfunc tp_setattr - __setattr__ */
    NULL,  /* cmpfunc tp_compare - __cmp__ */
    dawg_repr,  /* reprfunc tp_repr - __repr__ */
    0,  /* PyNumberMethods *tp_as_number */
    0,  /* PySequenceMethods *tp_as_sequence */
    0,  /* PyMappingMethods *tp_as_mappking */
    NULL,  /* hashfunc tp_hash - __hash__ */
    NULL,  /* ternaryfunc tp_call - __call__ */
    dawg_repr,  /* reprfunc tp_str - __str__ */
};


PyObject *dawg_NEW()
{
    dawg *object = NULL;
    object = PyObject_NEW(dawg, &dawg_Type);
    if(object != NULL)
        object->dawg = yodawg_create();
    return (PyObject *)object;
}

void dawg_dealloc(PyObject *self)
{
    //yodawg_free_dawg((dawg *)(self)->dawg);
    PyMem_DEL(self);
}

PyObject *dawg_new(PyObject *self, PyObject *args)
{
    PyObject *object = NULL;
    object = dawg_NEW();
    return object;
}

int dawg_print(PyObject *self, FILE *fp, int flags)
{
    fprintf(fp, "<dawg>");
    return 0;
}

PyObject *dawg_repr(PyObject *self)
{
    return PyString_FromString("<dawg>");
}


PyObject *Dawg_init(PyObject *self, PyObject *args)
{
    struct yonode *dawg;
    dawg = yodawg_create();
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *Dawg_add(PyObject *self, PyObject *args)
{
}

PyObject *Dawg_complete(PyObject *self, PyObject *args)
{
}

static PyMethodDef DawgMethods[] = {
    {"__init__", Dawg_init, METH_NOARGS,
        "Create a new DAWG."},
    {"add", Dawg_add, METH_VARARGS,
        "Add a bytestring to the DAWG."},
    {"complete", Dawg_complete, METH_VARARGS,
        "Get a set of possible complete strings given a prefix."},
};

static PyMethodDef ModuleMethods[] = { {NULL} };

PyMODINIT_FUNC initdawgs()
{
    PyMethodDef *def;

    /* Create the module and class. */
    PyObject *module = Py_InitModule3("yodawg", ModuleMethods,
        "Efficiently store Directed Acyclic Word Graphs.");
    PyObject *moduleDict = PyModule_GetDict(module);
    PyObject *classDict = PyDict_New();
    PyObject *className = PyString_FromString("Dawg");
    PyObject *dawgClass = PyClass_New(NULL, classDict, className);
    PyDict_SetItemString(moduleDict, "Dawg", dawgClass);
    Py_DECREF(classDict);
    Py_DECREF(className);
    Py_DECREF(dawgClass);

    /* Add methods to class */
    for(def = DawgMethods; def->ml_name != NULL; def++) {
        PyObject *func = PyCFunction_New(def, NULL);
        PyObject *method = PyMethod_New(func, NULL, dawgClass);
        PyDict_SetItemString(classDict, def->ml_name, method);
        Py_DECREF(func);
        Py_DECREF(method);
    }
}
