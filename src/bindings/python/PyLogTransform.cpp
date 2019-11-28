// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the OpenColorIO Project.

#include <Python.h>
#include <OpenColorIO/OpenColorIO.h>

#include "PyUtil.h"
#include "PyDoc.h"

#define GetConstLogTransform(pyobject) GetConstPyOCIO<PyOCIO_Transform, \
    ConstLogTransformRcPtr, LogTransform>(pyobject, \
    PyOCIO_LogTransformType)

#define GetEditableLogTransform(pyobject) GetEditablePyOCIO<PyOCIO_Transform, \
    LogTransformRcPtr, LogTransform>(pyobject, \
    PyOCIO_LogTransformType)

namespace OCIO_NAMESPACE
{

namespace
{

///////////////////////////////////////////////////////////////////////
///

int PyOCIO_LogTransform_init(PyOCIO_Transform * self, PyObject * args, PyObject * kwds);
PyObject * PyOCIO_LogTransform_getBase(PyObject * self, PyObject *);
PyObject * PyOCIO_LogTransform_setBase(PyObject * self, PyObject * args);

///////////////////////////////////////////////////////////////////////
///

PyMethodDef PyOCIO_LogTransform_methods[] = {
    { "getBase",
    (PyCFunction) PyOCIO_LogTransform_getBase, METH_NOARGS, LOGTRANSFORM_GETBASE__DOC__ },
    { "setBase",
    PyOCIO_LogTransform_setBase, METH_VARARGS, LOGTRANSFORM_SETBASE__DOC__ },
    { NULL, NULL, 0, NULL }
};

}

///////////////////////////////////////////////////////////////////////////
///

PyTypeObject PyOCIO_LogTransformType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    OCIO_PYTHON_NAMESPACE(LogTransform),        //tp_name
    sizeof(PyOCIO_Transform),                   //tp_basicsize
    0,                                          //tp_itemsize
    0,                                          //tp_dealloc
    0,                                          //tp_print
    0,                                          //tp_getattr
    0,                                          //tp_setattr
    0,                                          //tp_compare
    0,                                          //tp_repr
    0,                                          //tp_as_number
    0,                                          //tp_as_sequence
    0,                                          //tp_as_mapping
    0,                                          //tp_hash 
    0,                                          //tp_call
    0,                                          //tp_str
    0,                                          //tp_getattro
    0,                                          //tp_setattro
    0,                                          //tp_as_buffer
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,   //tp_flags
    LOGTRANSFORM__DOC__,                        //tp_doc 
    0,                                          //tp_traverse 
    0,                                          //tp_clear 
    0,                                          //tp_richcompare 
    0,                                          //tp_weaklistoffset 
    0,                                          //tp_iter 
    0,                                          //tp_iternext 
    PyOCIO_LogTransform_methods,                //tp_methods 
    0,                                          //tp_members 
    0,                                          //tp_getset 
    &PyOCIO_TransformType,                      //tp_base 
    0,                                          //tp_dict 
    0,                                          //tp_descr_get 
    0,                                          //tp_descr_set 
    0,                                          //tp_dictoffset 
    (initproc) PyOCIO_LogTransform_init,        //tp_init 
    0,                                          //tp_alloc 
    0,                                          //tp_new 
    0,                                          //tp_free
    0,                                          //tp_is_gc
};

namespace
{

///////////////////////////////////////////////////////////////////////
///

int PyOCIO_LogTransform_init(PyOCIO_Transform * self, PyObject * args, PyObject * kwds)
{
    OCIO_PYTRY_ENTER()
    static const char *kwlist[] = { "base", "direction", NULL };
    float base = -1.0f; // -1.0 is an illegal value for log transform base
    char* direction = NULL;
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "|fs",
        const_cast<char **>(kwlist),
        &base, &direction )) return -1;
    LogTransformRcPtr ptr = LogTransform::Create();
    int ret = BuildPyTransformObject<LogTransformRcPtr>(self, ptr);
    if(base != -1.0f)
        ptr->setBase(base);
    if(direction)
        ptr->setDirection(TransformDirectionFromString(direction));
    return ret;
    OCIO_PYTRY_EXIT(-1)
}

PyObject * PyOCIO_LogTransform_getBase(PyObject * self, PyObject *)
{
    OCIO_PYTRY_ENTER()
    ConstLogTransformRcPtr transform = GetConstLogTransform(self);
    return PyFloat_FromDouble(transform->getBase());
    OCIO_PYTRY_EXIT(NULL)
}

PyObject * PyOCIO_LogTransform_setBase(PyObject * self, PyObject * args)
{
    OCIO_PYTRY_ENTER()
    float base;
    if (!PyArg_ParseTuple(args, "f:setBase",
        &base)) return NULL;
    LogTransformRcPtr transform = GetEditableLogTransform(self);
    transform->setBase(base);
    Py_RETURN_NONE;
    OCIO_PYTRY_EXIT(NULL)
}

}

} // namespace OCIO_NAMESPACE
