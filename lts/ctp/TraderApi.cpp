#define PY_SSIZE_T_CLEAN
#ifndef CYTHON_USE_PYLONG_INTERNALS
#ifdef PYLONG_BITS_IN_DIGIT
#define CYTHON_USE_PYLONG_INTERNALS 0
#else
#include "pyconfig.h"
#ifdef PYLONG_BITS_IN_DIGIT
#define CYTHON_USE_PYLONG_INTERNALS 1
#else
#define CYTHON_USE_PYLONG_INTERNALS 0
#endif
#endif
#endif
#include "Python.h"
#ifndef Py_PYTHON_H
    #error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x02040000
    #error Cython requires Python 2.4+.
#else
#define CYTHON_ABI "0_20_2"
#include <stddef.h> 
#ifndef offsetof
#define offsetof(type, member) ( (size_t) & ((type*)0) -> member )
#endif
#if !defined(WIN32) && !defined(MS_WINDOWS)
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
  #ifndef __fastcall
    #define __fastcall
  #endif
#endif
#ifndef DL_IMPORT
  #define DL_IMPORT(t) t
#endif
#ifndef DL_EXPORT
  #define DL_EXPORT(t) t
#endif
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#ifndef Py_HUGE_VAL
  #define Py_HUGE_VAL HUGE_VAL
#endif
#ifdef PYPY_VERSION
#define CYTHON_COMPILING_IN_PYPY 1
#define CYTHON_COMPILING_IN_CPYTHON 0
#else
#define CYTHON_COMPILING_IN_PYPY 0
#define CYTHON_COMPILING_IN_CPYTHON 1
#endif
#if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX < 0x02070600
#define Py_OptimizeFlag 0
#endif
#if PY_VERSION_HEX < 0x02050000
  typedef int Py_ssize_t;
  #define PY_SSIZE_T_MAX INT_MAX
  #define PY_SSIZE_T_MIN INT_MIN
  #define PY_FORMAT_SIZE_T ""
  #define CYTHON_FORMAT_SSIZE_T ""
  #define PyInt_FromSsize_t(z) PyInt_FromLong(z)
  #define PyInt_AsSsize_t(o) __Pyx_PyInt_As_int(o)
  #define PyNumber_Index(o) ((PyNumber_Check(o) && !PyFloat_Check(o)) ? PyNumber_Int(o) : \
                                (PyErr_Format(PyExc_TypeError, \
                                              "expected index value, got %.200s", Py_TYPE(o)->tp_name), \
                                 (PyObject*)0))
  #define __Pyx_PyIndex_Check(o) (PyNumber_Check(o) && !PyFloat_Check(o) && \
                                  !PyComplex_Check(o))
  #define PyIndex_Check __Pyx_PyIndex_Check
  #define PyErr_WarnEx(category, message, stacklevel) PyErr_Warn(category, message)
  #define __PYX_BUILD_PY_SSIZE_T "i"
#else
  #define __PYX_BUILD_PY_SSIZE_T "n"
  #define CYTHON_FORMAT_SSIZE_T "z"
  #define __Pyx_PyIndex_Check PyIndex_Check
#endif
#if PY_VERSION_HEX < 0x02060000
  #define Py_REFCNT(ob) (((PyObject*)(ob))->ob_refcnt)
  #define Py_TYPE(ob) (((PyObject*)(ob))->ob_type)
  #define Py_SIZE(ob) (((PyVarObject*)(ob))->ob_size)
  #define PyVarObject_HEAD_INIT(type, size) \
          PyObject_HEAD_INIT(type) size,
  #define PyType_Modified(t)
  typedef struct {
     void *buf;
     PyObject *obj;
     Py_ssize_t len;
     Py_ssize_t itemsize;
     int readonly;
     int ndim;
     char *format;
     Py_ssize_t *shape;
     Py_ssize_t *strides;
     Py_ssize_t *suboffsets;
     void *internal;
  } Py_buffer;
  #define PyBUF_SIMPLE 0
  #define PyBUF_WRITABLE 0x0001
  #define PyBUF_FORMAT 0x0004
  #define PyBUF_ND 0x0008
  #define PyBUF_STRIDES (0x0010 | PyBUF_ND)
  #define PyBUF_C_CONTIGUOUS (0x0020 | PyBUF_STRIDES)
  #define PyBUF_F_CONTIGUOUS (0x0040 | PyBUF_STRIDES)
  #define PyBUF_ANY_CONTIGUOUS (0x0080 | PyBUF_STRIDES)
  #define PyBUF_INDIRECT (0x0100 | PyBUF_STRIDES)
  #define PyBUF_RECORDS (PyBUF_STRIDES | PyBUF_FORMAT | PyBUF_WRITABLE)
  #define PyBUF_FULL (PyBUF_INDIRECT | PyBUF_FORMAT | PyBUF_WRITABLE)
  typedef int (*getbufferproc)(PyObject *, Py_buffer *, int);
  typedef void (*releasebufferproc)(PyObject *, Py_buffer *);
#endif
#if PY_MAJOR_VERSION < 3
  #define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos) \
          PyCode_New(a+k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyClass_Type
#else
  #define __Pyx_BUILTIN_MODULE_NAME "builtins"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos) \
          PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyType_Type
#endif
#if PY_VERSION_HEX < 0x02060000
  #define PyUnicode_FromString(s) PyUnicode_Decode(s, strlen(s), "UTF-8", "strict")
#endif
#if PY_MAJOR_VERSION >= 3
  #define Py_TPFLAGS_CHECKTYPES 0
  #define Py_TPFLAGS_HAVE_INDEX 0
#endif
#if (PY_VERSION_HEX < 0x02060000) || (PY_MAJOR_VERSION >= 3)
  #define Py_TPFLAGS_HAVE_NEWBUFFER 0
#endif
#if PY_VERSION_HEX < 0x02060000
  #define Py_TPFLAGS_HAVE_VERSION_TAG 0
#endif
#if PY_VERSION_HEX < 0x02060000 && !defined(Py_TPFLAGS_IS_ABSTRACT)
  #define Py_TPFLAGS_IS_ABSTRACT 0
#endif
#if PY_VERSION_HEX < 0x030400a1 && !defined(Py_TPFLAGS_HAVE_FINALIZE)
  #define Py_TPFLAGS_HAVE_FINALIZE 0
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
  #define CYTHON_PEP393_ENABLED 1
  #define __Pyx_PyUnicode_READY(op) (likely(PyUnicode_IS_READY(op)) ? \
                                              0 : _PyUnicode_Ready((PyObject *)(op)))
  #define __Pyx_PyUnicode_GET_LENGTH(u) PyUnicode_GET_LENGTH(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
  #define __Pyx_PyUnicode_KIND(u) PyUnicode_KIND(u)
  #define __Pyx_PyUnicode_DATA(u) PyUnicode_DATA(u)
  #define __Pyx_PyUnicode_READ(k, d, i) PyUnicode_READ(k, d, i)
#else
  #define CYTHON_PEP393_ENABLED 0
  #define __Pyx_PyUnicode_READY(op) (0)
  #define __Pyx_PyUnicode_GET_LENGTH(u) PyUnicode_GET_SIZE(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
  #define __Pyx_PyUnicode_KIND(u) (sizeof(Py_UNICODE))
  #define __Pyx_PyUnicode_DATA(u) ((void*)PyUnicode_AS_UNICODE(u))
  #define __Pyx_PyUnicode_READ(k, d, i) ((void)(k), (Py_UCS4)(((Py_UNICODE*)d)[i]))
#endif
#if CYTHON_COMPILING_IN_PYPY
  #define __Pyx_PyUnicode_Concat(a, b) PyNumber_Add(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b) PyNumber_Add(a, b)
#else
  #define __Pyx_PyUnicode_Concat(a, b) PyUnicode_Concat(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b) ((unlikely((a) == Py_None) || unlikely((b) == Py_None)) ? \
      PyNumber_Add(a, b) : __Pyx_PyUnicode_Concat(a, b))
#endif
#define __Pyx_PyString_FormatSafe(a, b) ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : __Pyx_PyString_Format(a, b))
#define __Pyx_PyUnicode_FormatSafe(a, b) ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : PyUnicode_Format(a, b))
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyString_Format(a, b) PyUnicode_Format(a, b)
#else
  #define __Pyx_PyString_Format(a, b) PyString_Format(a, b)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBaseString_Type PyUnicode_Type
  #define PyStringObject PyUnicodeObject
  #define PyString_Type PyUnicode_Type
  #define PyString_Check PyUnicode_Check
  #define PyString_CheckExact PyUnicode_CheckExact
#endif
#if PY_VERSION_HEX < 0x02060000
  #define PyBytesObject PyStringObject
  #define PyBytes_Type PyString_Type
  #define PyBytes_Check PyString_Check
  #define PyBytes_CheckExact PyString_CheckExact
  #define PyBytes_FromString PyString_FromString
  #define PyBytes_FromStringAndSize PyString_FromStringAndSize
  #define PyBytes_FromFormat PyString_FromFormat
  #define PyBytes_DecodeEscape PyString_DecodeEscape
  #define PyBytes_AsString PyString_AsString
  #define PyBytes_AsStringAndSize PyString_AsStringAndSize
  #define PyBytes_Size PyString_Size
  #define PyBytes_AS_STRING PyString_AS_STRING
  #define PyBytes_GET_SIZE PyString_GET_SIZE
  #define PyBytes_Repr PyString_Repr
  #define PyBytes_Concat PyString_Concat
  #define PyBytes_ConcatAndDel PyString_ConcatAndDel
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyBaseString_Check(obj) PyUnicode_Check(obj)
  #define __Pyx_PyBaseString_CheckExact(obj) PyUnicode_CheckExact(obj)
#else
  #define __Pyx_PyBaseString_Check(obj) (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj) || \
                                         PyString_Check(obj) || PyUnicode_Check(obj))
  #define __Pyx_PyBaseString_CheckExact(obj) (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj))
#endif
#if PY_VERSION_HEX < 0x02060000
  #define PySet_Check(obj) PyObject_TypeCheck(obj, &PySet_Type)
  #define PyFrozenSet_Check(obj) PyObject_TypeCheck(obj, &PyFrozenSet_Type)
#endif
#ifndef PySet_CheckExact
  #define PySet_CheckExact(obj) (Py_TYPE(obj) == &PySet_Type)
#endif
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#if PY_MAJOR_VERSION >= 3
  #define PyIntObject PyLongObject
  #define PyInt_Type PyLong_Type
  #define PyInt_Check(op) PyLong_Check(op)
  #define PyInt_CheckExact(op) PyLong_CheckExact(op)
  #define PyInt_FromString PyLong_FromString
  #define PyInt_FromUnicode PyLong_FromUnicode
  #define PyInt_FromLong PyLong_FromLong
  #define PyInt_FromSize_t PyLong_FromSize_t
  #define PyInt_FromSsize_t PyLong_FromSsize_t
  #define PyInt_AsLong PyLong_AsLong
  #define PyInt_AS_LONG PyLong_AS_LONG
  #define PyInt_AsSsize_t PyLong_AsSsize_t
  #define PyInt_AsUnsignedLongMask PyLong_AsUnsignedLongMask
  #define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
  #define PyNumber_Int PyNumber_Long
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBoolObject PyLongObject
#endif
#if PY_VERSION_HEX < 0x030200A4
  typedef long Py_hash_t;
  #define __Pyx_PyInt_FromHash_t PyInt_FromLong
  #define __Pyx_PyInt_AsHash_t PyInt_AsLong
#else
  #define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
  #define __Pyx_PyInt_AsHash_t PyInt_AsSsize_t
#endif
#if (PY_MAJOR_VERSION < 3) || (PY_VERSION_HEX >= 0x03010300)
  #define __Pyx_PySequence_GetSlice(obj, a, b) PySequence_GetSlice(obj, a, b)
  #define __Pyx_PySequence_SetSlice(obj, a, b, value) PySequence_SetSlice(obj, a, b, value)
  #define __Pyx_PySequence_DelSlice(obj, a, b) PySequence_DelSlice(obj, a, b)
#else
  #define __Pyx_PySequence_GetSlice(obj, a, b) (unlikely(!(obj)) ? \
        (PyErr_SetString(PyExc_SystemError, "null argument to internal routine"), (PyObject*)0) : \
        (likely((obj)->ob_type->tp_as_mapping) ? (PySequence_GetSlice(obj, a, b)) : \
            (PyErr_Format(PyExc_TypeError, "'%.200s' object is unsliceable", (obj)->ob_type->tp_name), (PyObject*)0)))
  #define __Pyx_PySequence_SetSlice(obj, a, b, value) (unlikely(!(obj)) ? \
        (PyErr_SetString(PyExc_SystemError, "null argument to internal routine"), -1) : \
        (likely((obj)->ob_type->tp_as_mapping) ? (PySequence_SetSlice(obj, a, b, value)) : \
            (PyErr_Format(PyExc_TypeError, "'%.200s' object doesn't support slice assignment", (obj)->ob_type->tp_name), -1)))
  #define __Pyx_PySequence_DelSlice(obj, a, b) (unlikely(!(obj)) ? \
        (PyErr_SetString(PyExc_SystemError, "null argument to internal routine"), -1) : \
        (likely((obj)->ob_type->tp_as_mapping) ? (PySequence_DelSlice(obj, a, b)) : \
            (PyErr_Format(PyExc_TypeError, "'%.200s' object doesn't support slice deletion", (obj)->ob_type->tp_name), -1)))
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyMethod_New(func, self, klass) ((self) ? PyMethod_New(func, self) : PyInstanceMethod_New(func))
#endif
#if PY_VERSION_HEX < 0x02050000
  #define __Pyx_GetAttrString(o,n) PyObject_GetAttrString((o),((char *)(n)))
  #define __Pyx_SetAttrString(o,n,a) PyObject_SetAttrString((o),((char *)(n)),(a))
  #define __Pyx_DelAttrString(o,n) PyObject_DelAttrString((o),((char *)(n)))
#else
  #define __Pyx_GetAttrString(o,n) PyObject_GetAttrString((o),(n))
  #define __Pyx_SetAttrString(o,n,a) PyObject_SetAttrString((o),(n),(a))
  #define __Pyx_DelAttrString(o,n) PyObject_DelAttrString((o),(n))
#endif
#if PY_VERSION_HEX < 0x02050000
  #define __Pyx_NAMESTR(n) ((char *)(n))
  #define __Pyx_DOCSTR(n) ((char *)(n))
#else
  #define __Pyx_NAMESTR(n) (n)
  #define __Pyx_DOCSTR(n) (n)
#endif
#ifndef CYTHON_INLINE
  #if defined(__GNUC__)
    #define CYTHON_INLINE __inline__
  #elif defined(_MSC_VER)
    #define CYTHON_INLINE __inline
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_INLINE inline
  #else
    #define CYTHON_INLINE
  #endif
#endif
#ifndef CYTHON_RESTRICT
  #if defined(__GNUC__)
    #define CYTHON_RESTRICT __restrict__
  #elif defined(_MSC_VER) && _MSC_VER >= 1400
    #define CYTHON_RESTRICT __restrict
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_RESTRICT restrict
  #else
    #define CYTHON_RESTRICT
  #endif
#endif
#ifdef NAN
#define __PYX_NAN() ((float) NAN)
#else
static CYTHON_INLINE float __PYX_NAN() {
  float value;
  memset(&value, 0xFF, sizeof(value));
  return value;
}
#endif
#ifdef __cplusplus
template<typename T>
void __Pyx_call_destructor(T* x) {
    x->~T();
}
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyNumber_Divide(x,y) PyNumber_TrueDivide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y) PyNumber_InPlaceTrueDivide(x,y)
#else
  #define __Pyx_PyNumber_Divide(x,y) PyNumber_Divide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y) PyNumber_InPlaceDivide(x,y)
#endif
#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif
#if defined(WIN32) || defined(MS_WINDOWS)
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#define __PYX_HAVE__lts___TraderApi
#define __PYX_HAVE_API__lts___TraderApi
#include "SecurityFtdcUserApiDataType.h"
#include "SecurityFtdcUserApiStruct.h"
#include "string.h"
#include "SecurityFtdcTraderApi.h"
#include "ios"
#include "new"
#include "stdexcept"
#include "typeinfo"
#include "CTraderApi.h"
#ifdef _OPENMP
#include <omp.h>
#endif 
#ifdef PYREX_WITHOUT_ASSERTIONS
#define CYTHON_WITHOUT_ASSERTIONS
#endif
#ifndef CYTHON_UNUSED
#if defined(__GNUC__)
#if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#define CYTHON_UNUSED __attribute__ ((__unused__))
#else
#define CYTHON_UNUSED
#endif
#elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#define CYTHON_UNUSED __attribute__ ((__unused__))
#else
#define CYTHON_UNUSED
#endif
#endif
typedef struct {PyObject **p; char *s; const Py_ssize_t n; const char* encoding;
                const char is_unicode; const char is_str; const char intern; } __Pyx_StringTabEntry; 
#define __PYX_DEFAULT_STRING_ENCODING_IS_ASCII 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT 0
#define __PYX_DEFAULT_STRING_ENCODING ""
#define __Pyx_PyObject_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyObject_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#define __Pyx_fits_Py_ssize_t(v, type, is_signed) ( \
    (sizeof(type) < sizeof(Py_ssize_t)) || \
    (sizeof(type) > sizeof(Py_ssize_t) && \
          likely(v < (type)PY_SSIZE_T_MAX || \
                 v == (type)PY_SSIZE_T_MAX) && \
          (!is_signed || likely(v > (type)PY_SSIZE_T_MIN || \
                                v == (type)PY_SSIZE_T_MIN))) || \
    (sizeof(type) == sizeof(Py_ssize_t) && \
          (is_signed || likely(v < (type)PY_SSIZE_T_MAX || \
                               v == (type)PY_SSIZE_T_MAX))) )
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject*);
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject*, Py_ssize_t* length);
#define __Pyx_PyByteArray_FromString(s) PyByteArray_FromStringAndSize((const char*)s, strlen((const char*)s))
#define __Pyx_PyByteArray_FromStringAndSize(s, l) PyByteArray_FromStringAndSize((const char*)s, l)
#define __Pyx_PyBytes_FromString PyBytes_FromString
#define __Pyx_PyBytes_FromStringAndSize PyBytes_FromStringAndSize
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char*);
#if PY_MAJOR_VERSION < 3
    #define __Pyx_PyStr_FromString __Pyx_PyBytes_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#else
    #define __Pyx_PyStr_FromString __Pyx_PyUnicode_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyUnicode_FromStringAndSize
#endif
#define __Pyx_PyObject_AsSString(s) ((signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsUString(s) ((unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_FromUString(s) __Pyx_PyObject_FromString((const char*)s)
#define __Pyx_PyBytes_FromUString(s) __Pyx_PyBytes_FromString((const char*)s)
#define __Pyx_PyByteArray_FromUString(s) __Pyx_PyByteArray_FromString((const char*)s)
#define __Pyx_PyStr_FromUString(s) __Pyx_PyStr_FromString((const char*)s)
#define __Pyx_PyUnicode_FromUString(s) __Pyx_PyUnicode_FromString((const char*)s)
#if PY_MAJOR_VERSION < 3
static CYTHON_INLINE size_t __Pyx_Py_UNICODE_strlen(const Py_UNICODE *u)
{
    const Py_UNICODE *u_end = u;
    while (*u_end++) ;
    return (size_t)(u_end - u - 1);
}
#else
#define __Pyx_Py_UNICODE_strlen Py_UNICODE_strlen
#endif
#define __Pyx_PyUnicode_FromUnicode(u) PyUnicode_FromUnicode(u, __Pyx_Py_UNICODE_strlen(u))
#define __Pyx_PyUnicode_FromUnicodeAndLength PyUnicode_FromUnicode
#define __Pyx_PyUnicode_AsUnicode PyUnicode_AsUnicode
#define __Pyx_Owned_Py_None(b) (Py_INCREF(Py_None), Py_None)
#define __Pyx_PyBool_FromLong(b) ((b) ? (Py_INCREF(Py_True), Py_True) : (Py_INCREF(Py_False), Py_False))
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyNumber_Int(PyObject* x);
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject*);
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t);
#if CYTHON_COMPILING_IN_CPYTHON
#define __pyx_PyFloat_AsDouble(x) (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float) __pyx_PyFloat_AsDouble(x))
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
static int __Pyx_sys_getdefaultencoding_not_ascii;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    PyObject* ascii_chars_u = NULL;
    PyObject* ascii_chars_b = NULL;
    const char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    if (strcmp(default_encoding_c, "ascii") == 0) {
        __Pyx_sys_getdefaultencoding_not_ascii = 0;
    } else {
        char ascii_chars[128];
        int c;
        for (c = 0; c < 128; c++) {
            ascii_chars[c] = c;
        }
        __Pyx_sys_getdefaultencoding_not_ascii = 1;
        ascii_chars_u = PyUnicode_DecodeASCII(ascii_chars, 128, NULL);
        if (!ascii_chars_u) goto bad;
        ascii_chars_b = PyUnicode_AsEncodedString(ascii_chars_u, default_encoding_c, NULL);
        if (!ascii_chars_b || !PyBytes_Check(ascii_chars_b) || memcmp(ascii_chars, PyBytes_AS_STRING(ascii_chars_b), 128) != 0) {
            PyErr_Format(
                PyExc_ValueError,
                "This module compiled with c_string_encoding=ascii, but default encoding '%.200s' is not a superset of ascii.",
                default_encoding_c);
            goto bad;
        }
        Py_DECREF(ascii_chars_u);
        Py_DECREF(ascii_chars_b);
    }
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    Py_XDECREF(ascii_chars_u);
    Py_XDECREF(ascii_chars_b);
    return -1;
}
#endif
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT && PY_MAJOR_VERSION >= 3
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_DecodeUTF8(c_str, size, NULL)
#else
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_Decode(c_str, size, __PYX_DEFAULT_STRING_ENCODING, NULL)
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
static char* __PYX_DEFAULT_STRING_ENCODING;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    __PYX_DEFAULT_STRING_ENCODING = (char*) malloc(strlen(default_encoding_c));
    if (!__PYX_DEFAULT_STRING_ENCODING) goto bad;
    strcpy(__PYX_DEFAULT_STRING_ENCODING, default_encoding_c);
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    return -1;
}
#endif
#endif
#if defined(__GNUC__) && (__GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95)))
  #define likely(x) __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else 
  #define likely(x) (x)
  #define unlikely(x) (x)
#endif 
static PyObject *__pyx_m;
static PyObject *__pyx_d;
static PyObject *__pyx_b;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char * __pyx_cfilenm= __FILE__;
static const char *__pyx_filename;
static const char *__pyx_f[] = {
  "TraderApi.pyx",
};
struct __pyx_obj_3lts_10_TraderApi_TraderApi;
struct __pyx_obj_3lts_10_TraderApi_TraderApi {
  PyObject_HEAD
  CSecurityFtdcTraderApi *api;
  CTraderSpi *spi;
};
#ifndef CYTHON_REFNANNY
  #define CYTHON_REFNANNY 0
#endif
#if CYTHON_REFNANNY
  typedef struct {
    void (*INCREF)(void*, PyObject*, int);
    void (*DECREF)(void*, PyObject*, int);
    void (*GOTREF)(void*, PyObject*, int);
    void (*GIVEREF)(void*, PyObject*, int);
    void* (*SetupContext)(const char*, int, const char*);
    void (*FinishContext)(void**);
  } __Pyx_RefNannyAPIStruct;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname); 
  #define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
  #define __Pyx_RefNannySetupContext(name, acquire_gil) \
          if (acquire_gil) { \
              PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure(); \
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
              PyGILState_Release(__pyx_gilstate_save); \
          } else { \
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
          }
#else
  #define __Pyx_RefNannySetupContext(name, acquire_gil) \
          __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
  #define __Pyx_RefNannyFinishContext() \
          __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
  #define __Pyx_INCREF(r) __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_DECREF(r) __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GOTREF(r) __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GIVEREF(r) __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_XINCREF(r) do { if((r) != NULL) {__Pyx_INCREF(r); }} while(0)
  #define __Pyx_XDECREF(r) do { if((r) != NULL) {__Pyx_DECREF(r); }} while(0)
  #define __Pyx_XGOTREF(r) do { if((r) != NULL) {__Pyx_GOTREF(r); }} while(0)
  #define __Pyx_XGIVEREF(r) do { if((r) != NULL) {__Pyx_GIVEREF(r);}} while(0)
#else
  #define __Pyx_RefNannyDeclarations
  #define __Pyx_RefNannySetupContext(name, acquire_gil)
  #define __Pyx_RefNannyFinishContext()
  #define __Pyx_INCREF(r) Py_INCREF(r)
  #define __Pyx_DECREF(r) Py_DECREF(r)
  #define __Pyx_GOTREF(r)
  #define __Pyx_GIVEREF(r)
  #define __Pyx_XINCREF(r) Py_XINCREF(r)
  #define __Pyx_XDECREF(r) Py_XDECREF(r)
  #define __Pyx_XGOTREF(r)
  #define __Pyx_XGIVEREF(r)
#endif 
#define __Pyx_XDECREF_SET(r, v) do { \
        PyObject *tmp = (PyObject *) r; \
        r = v; __Pyx_XDECREF(tmp); \
    } while (0)
#define __Pyx_DECREF_SET(r, v) do { \
        PyObject *tmp = (PyObject *) r; \
        r = v; __Pyx_DECREF(tmp); \
    } while (0)
#define __Pyx_CLEAR(r) do { PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);} while(0)
#define __Pyx_XCLEAR(r) do { if((r) != NULL) {PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);}} while(0)
static void __Pyx_RaiseDoubleKeywordsError(const char* func_name, PyObject* kw_name); 
static int __Pyx_ParseOptionalKeywords(PyObject *kwds, PyObject **argnames[], \
    PyObject *kwds2, PyObject *values[], Py_ssize_t num_pos_args, \
    const char* function_name); 
static void __Pyx_RaiseArgtupleInvalid(const char* func_name, int exact,
    Py_ssize_t num_min, Py_ssize_t num_max, Py_ssize_t num_found); 
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw); 
#else
#define __Pyx_PyObject_Call(func, arg, kw) PyObject_Call(func, arg, kw)
#endif
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name) {
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_getattro))
        return tp->tp_getattro(obj, attr_name);
#if PY_MAJOR_VERSION < 3
    if (likely(tp->tp_getattr))
        return tp->tp_getattr(obj, PyString_AS_STRING(attr_name));
#endif
    return PyObject_GetAttr(obj, attr_name);
}
#else
#define __Pyx_PyObject_GetAttrStr(o,n) PyObject_GetAttr(o,n)
#endif
static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *);
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value);
#ifndef __Pyx_CppExn2PyErr
#include <new>
#include <typeinfo>
#include <stdexcept>
#include <ios>
static void __Pyx_CppExn2PyErr() {
  try {
    if (PyErr_Occurred())
      ; 
    else
      throw;
  } catch (const std::bad_alloc& exn) {
    PyErr_SetString(PyExc_MemoryError, exn.what());
  } catch (const std::bad_cast& exn) {
    PyErr_SetString(PyExc_TypeError, exn.what());
  } catch (const std::domain_error& exn) {
    PyErr_SetString(PyExc_ValueError, exn.what());
  } catch (const std::invalid_argument& exn) {
    PyErr_SetString(PyExc_ValueError, exn.what());
  } catch (const std::ios_base::failure& exn) {
    PyErr_SetString(PyExc_IOError, exn.what());
  } catch (const std::out_of_range& exn) {
    PyErr_SetString(PyExc_IndexError, exn.what());
  } catch (const std::overflow_error& exn) {
    PyErr_SetString(PyExc_OverflowError, exn.what());
  } catch (const std::range_error& exn) {
    PyErr_SetString(PyExc_ArithmeticError, exn.what());
  } catch (const std::underflow_error& exn) {
    PyErr_SetString(PyExc_ArithmeticError, exn.what());
  } catch (const std::exception& exn) {
    PyErr_SetString(PyExc_RuntimeError, exn.what());
  }
  catch (...)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unknown exception");
  }
}
#endif
#ifndef __PYX_FORCE_INIT_THREADS
  #define __PYX_FORCE_INIT_THREADS 0
#endif
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_int(int value);
static CYTHON_INLINE size_t __Pyx_PyInt_As_size_t(PyObject *);
static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *);
static int __Pyx_check_binary_version(void);
typedef struct {
    int code_line;
    PyCodeObject* code_object;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
    int count;
    int max_count;
    __Pyx_CodeObjectCacheEntry* entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0,0,NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object);
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename); 
static int __Pyx_InitStrings(__Pyx_StringTabEntry *t); 
static PyTypeObject *__pyx_ptype_3lts_10_TraderApi_TraderApi = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_addressof = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_BondInterest = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_DepthMarketData = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_Exchange = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_FundTransfer = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_InputFundTransfer = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_InputOrder = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_InputOrderAction = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_Instrument = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_InstrumentCommissionRate = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_Investor = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_InvestorPosition = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_MarketRationInfo = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_Order = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_OrderAction = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_RspUserLogin = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_Trade = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_TradingAccount = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_TradingAccountPasswordUpdate = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_TradingCode = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_UserLogout = 0;
static PyObject *__pyx_v_3lts_10_TraderApi_ApiStruct_UserPasswordUpdate = 0;
static void __pyx_f_3lts_10_TraderApi_TraderApi_Release(struct __pyx_obj_3lts_10_TraderApi_TraderApi *); 
#define __Pyx_MODULE_NAME "lts._TraderApi"
int __pyx_module_is_main_lts___TraderApi = 0;
static void __pyx_pf_3lts_10_TraderApi_9TraderApi___dealloc__(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_2Alive(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_4Create(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, const char *__pyx_v_pszFlowPath); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_6Release(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_8Init(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_10Join(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_12GetTradingDay(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_14RegisterFront(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, char *__pyx_v_pszFrontAddress); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_16SubscribePrivateTopic(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, enum SECURITY_TE_RESUME_TYPE __pyx_v_nResumeType); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_18SubscribePublicTopic(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, enum SECURITY_TE_RESUME_TYPE __pyx_v_nResumeType); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_20ReqUserLogin(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pReqUserLogin, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_22ReqUserLogout(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pUserLogout, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_24ReqOrderInsert(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pInputOrder, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_26ReqOrderAction(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pInputOrderAction, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_28ReqUserPasswordUpdate(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pUserPasswordUpdate, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_30ReqTradingAccountPasswordUpdate(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pTradingAccountPasswordUpdate, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_32ReqQryExchange(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryExchange, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_34ReqQryInstrument(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryInstrument, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_36ReqQryInvestor(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryInvestor, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_38ReqQryTradingCode(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryTradingCode, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_40ReqQryTradingAccount(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryTradingAccount, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_42ReqQryDepthMarketData(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryDepthMarketData, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_44ReqQryBondInterest(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryBondInterest, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_46ReqQryMarketRationInfo(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryMarketRationInfo, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_48ReqQryInstrumentCommissionRate(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryInstrumentCommissionRate, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_50ReqQryOrder(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryOrder, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_52ReqQryTrade(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryTrade, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_54ReqQryInvestorPosition(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryInvestorPosition, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_56ReqFundOutByLiber(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pInputFundTransfer, int __pyx_v_nRequestID); 
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_58ReqQryFundTransferSerial(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryFundTransferSerial, int __pyx_v_nRequestID); 
static PyObject *__pyx_tp_new_3lts_10_TraderApi_TraderApi(PyTypeObject *t, PyObject *a, PyObject *k); 
static char __pyx_k_[] = "";
static char __pyx_k_main[] = "__main__";
static char __pyx_k_test[] = "__test__";
static char __pyx_k_pQryOrder[] = "pQryOrder";
static char __pyx_k_pQryTrade[] = "pQryTrade";
static char __pyx_k_OnRspError[] = "OnRspError";
static char __pyx_k_OnRtnOrder[] = "OnRtnOrder";
static char __pyx_k_OnRtnTrade[] = "OnRtnTrade";
static char __pyx_k_nRequestID[] = "nRequestID";
static char __pyx_k_pInputOrder[] = "pInputOrder";
static char __pyx_k_pUserLogout[] = "pUserLogout";
static char __pyx_k_pszFlowPath[] = "pszFlowPath";
static char __pyx_k_pQryExchange[] = "pQryExchange";
static char __pyx_k_pQryInvestor[] = "pQryInvestor";
static char __pyx_k_OnRspQryOrder[] = "OnRspQryOrder";
static char __pyx_k_OnRspQryTrade[] = "OnRspQryTrade";
static char __pyx_k_pReqUserLogin[] = "pReqUserLogin";
static char __pyx_k_OnRspUserLogin[] = "OnRspUserLogin";
static char __pyx_k_pQryInstrument[] = "pQryInstrument";
static char __pyx_k_OnRspUserLogout[] = "OnRspUserLogout";
static char __pyx_k_pQryTradingCode[] = "pQryTradingCode";
static char __pyx_k_OnFrontConnected[] = "OnFrontConnected";
static char __pyx_k_OnRspOrderAction[] = "OnRspOrderAction";
static char __pyx_k_OnRspOrderInsert[] = "OnRspOrderInsert";
static char __pyx_k_OnRspQryExchange[] = "OnRspQryExchange";
static char __pyx_k_OnRspQryInvestor[] = "OnRspQryInvestor";
static char __pyx_k_pQryBondInterest[] = "pQryBondInterest";
static char __pyx_k_OnRtnFundInByBank[] = "OnRtnFundInByBank";
static char __pyx_k_pInputOrderAction[] = "pInputOrderAction";
static char __pyx_k_OnHeartBeatWarning[] = "OnHeartBeatWarning";
static char __pyx_k_OnRspQryInstrument[] = "OnRspQryInstrument";
static char __pyx_k_pInputFundTransfer[] = "pInputFundTransfer";
static char __pyx_k_pQryTradingAccount[] = "pQryTradingAccount";
static char __pyx_k_OnErrRtnOrderAction[] = "OnErrRtnOrderAction";
static char __pyx_k_OnErrRtnOrderInsert[] = "OnErrRtnOrderInsert";
static char __pyx_k_OnFrontDisconnected[] = "OnFrontDisconnected";
static char __pyx_k_OnRspFundOutByLiber[] = "OnRspFundOutByLiber";
static char __pyx_k_OnRspQryTradingCode[] = "OnRspQryTradingCode";
static char __pyx_k_OnRtnFundOutByLiber[] = "OnRtnFundOutByLiber";
static char __pyx_k_pQryDepthMarketData[] = "pQryDepthMarketData";
static char __pyx_k_pUserPasswordUpdate[] = "pUserPasswordUpdate";
static char __pyx_k_OnRspQryBondInterest[] = "OnRspQryBondInterest";
static char __pyx_k_pQryInvestorPosition[] = "pQryInvestorPosition";
static char __pyx_k_pQryMarketRationInfo[] = "pQryMarketRationInfo";
static char __pyx_k_OnErrRtnFundOutByLiber[] = "OnErrRtnFundOutByLiber";
static char __pyx_k_OnRspQryTradingAccount[] = "OnRspQryTradingAccount";
static char __pyx_k_pQryFundTransferSerial[] = "pQryFundTransferSerial";
static char __pyx_k_OnRspQryDepthMarketData[] = "OnRspQryDepthMarketData";
static char __pyx_k_OnRspUserPasswordUpdate[] = "OnRspUserPasswordUpdate";
static char __pyx_k_OnRspQryInvestorPosition[] = "OnRspQryInvestorPosition";
static char __pyx_k_OnRspQryMarketRationInfo[] = "OnRspQryMarketRationInfo";
static char __pyx_k_OnRspQryFundTransferSerial[] = "OnRspQryFundTransferSerial";
static char __pyx_k_pQryInstrumentCommissionRate[] = "pQryInstrumentCommissionRate";
static char __pyx_k_pTradingAccountPasswordUpdate[] = "pTradingAccountPasswordUpdate";
static char __pyx_k_OnRspQryInstrumentCommissionRate[] = "OnRspQryInstrumentCommissionRate";
static char __pyx_k_OnRspTradingAccountPasswordUpdat[] = "OnRspTradingAccountPasswordUpdate";
static PyObject *__pyx_n_s_OnErrRtnFundOutByLiber;
static PyObject *__pyx_n_s_OnErrRtnOrderAction;
static PyObject *__pyx_n_s_OnErrRtnOrderInsert;
static PyObject *__pyx_n_s_OnFrontConnected;
static PyObject *__pyx_n_s_OnFrontDisconnected;
static PyObject *__pyx_n_s_OnHeartBeatWarning;
static PyObject *__pyx_n_s_OnRspError;
static PyObject *__pyx_n_s_OnRspFundOutByLiber;
static PyObject *__pyx_n_s_OnRspOrderAction;
static PyObject *__pyx_n_s_OnRspOrderInsert;
static PyObject *__pyx_n_s_OnRspQryBondInterest;
static PyObject *__pyx_n_s_OnRspQryDepthMarketData;
static PyObject *__pyx_n_s_OnRspQryExchange;
static PyObject *__pyx_n_s_OnRspQryFundTransferSerial;
static PyObject *__pyx_n_s_OnRspQryInstrument;
static PyObject *__pyx_n_s_OnRspQryInstrumentCommissionRate;
static PyObject *__pyx_n_s_OnRspQryInvestor;
static PyObject *__pyx_n_s_OnRspQryInvestorPosition;
static PyObject *__pyx_n_s_OnRspQryMarketRationInfo;
static PyObject *__pyx_n_s_OnRspQryOrder;
static PyObject *__pyx_n_s_OnRspQryTrade;
static PyObject *__pyx_n_s_OnRspQryTradingAccount;
static PyObject *__pyx_n_s_OnRspQryTradingCode;
static PyObject *__pyx_n_s_OnRspTradingAccountPasswordUpdat;
static PyObject *__pyx_n_s_OnRspUserLogin;
static PyObject *__pyx_n_s_OnRspUserLogout;
static PyObject *__pyx_n_s_OnRspUserPasswordUpdate;
static PyObject *__pyx_n_s_OnRtnFundInByBank;
static PyObject *__pyx_n_s_OnRtnFundOutByLiber;
static PyObject *__pyx_n_s_OnRtnOrder;
static PyObject *__pyx_n_s_OnRtnTrade;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_s_nRequestID;
static PyObject *__pyx_n_s_pInputFundTransfer;
static PyObject *__pyx_n_s_pInputOrder;
static PyObject *__pyx_n_s_pInputOrderAction;
static PyObject *__pyx_n_s_pQryBondInterest;
static PyObject *__pyx_n_s_pQryDepthMarketData;
static PyObject *__pyx_n_s_pQryExchange;
static PyObject *__pyx_n_s_pQryFundTransferSerial;
static PyObject *__pyx_n_s_pQryInstrument;
static PyObject *__pyx_n_s_pQryInstrumentCommissionRate;
static PyObject *__pyx_n_s_pQryInvestor;
static PyObject *__pyx_n_s_pQryInvestorPosition;
static PyObject *__pyx_n_s_pQryMarketRationInfo;
static PyObject *__pyx_n_s_pQryOrder;
static PyObject *__pyx_n_s_pQryTrade;
static PyObject *__pyx_n_s_pQryTradingAccount;
static PyObject *__pyx_n_s_pQryTradingCode;
static PyObject *__pyx_n_s_pReqUserLogin;
static PyObject *__pyx_n_s_pTradingAccountPasswordUpdate;
static PyObject *__pyx_n_s_pUserLogout;
static PyObject *__pyx_n_s_pUserPasswordUpdate;
static PyObject *__pyx_n_s_pszFlowPath;
static PyObject *__pyx_n_s_test;
PyObject *_init(CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_m) {
  PyObject *__pyx_v_fa = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("_init", 0);
  __pyx_t_1 = PyImport_ImportModule(S_ctypes); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 8; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttrString(__pyx_t_1, S_addressof); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 8; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = XStr(S_from_address); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 9; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_fa = __pyx_t_2;
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttrString(__pyx_v_m, S_BondInterest); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 10; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_v_fa); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 10; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_BondInterest);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_BondInterest, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttrString(__pyx_v_m, S_DepthMarketData); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_v_fa); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_DepthMarketData);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_DepthMarketData, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttrString(__pyx_v_m, S_Exchange); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 12; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_v_fa); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 12; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_Exchange);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_Exchange, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttrString(__pyx_v_m, S_FundTransfer); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 13; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_v_fa); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 13; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_FundTransfer);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_FundTransfer, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttrString(__pyx_v_m, S_InputFundTransfer); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 14; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_v_fa); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 14; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_InputFundTransfer);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_InputFundTransfer, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttrString(__pyx_v_m, S_InputOrder); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 15; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_v_fa); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 15; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_InputOrder);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_InputOrder, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttrString(__pyx_v_m, S_InputOrderAction); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 16; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_v_fa); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 16; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_InputOrderAction);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_InputOrderAction, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttrString(__pyx_v_m, S_Instrument); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 17; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_v_fa); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 17; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_Instrument);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_Instrument, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttrString(__pyx_v_m, S_InstrumentCommissionRate); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 18; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_v_fa); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 18; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_InstrumentCommissionRate);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_InstrumentCommissionRate, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttrString(__pyx_v_m, S_Investor); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 19; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_v_fa); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 19; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_Investor);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_Investor, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttrString(__pyx_v_m, S_InvestorPosition); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_v_fa); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_InvestorPosition);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_InvestorPosition, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttrString(__pyx_v_m, S_MarketRationInfo); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 21; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_v_fa); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 21; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_MarketRationInfo);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_MarketRationInfo, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttrString(__pyx_v_m, S_Order); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_v_fa); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_Order);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_Order, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttrString(__pyx_v_m, S_OrderAction); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_v_fa); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_OrderAction);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_OrderAction, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttrString(__pyx_v_m, S_RspInfo); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_v_fa); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttrString(__pyx_v_m, S_RspUserLogin); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 25; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_v_fa); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 25; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_RspUserLogin);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_RspUserLogin, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttrString(__pyx_v_m, S_Trade); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_v_fa); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_Trade);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_Trade, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttrString(__pyx_v_m, S_TradingAccount); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 27; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_v_fa); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 27; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_TradingAccount);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_TradingAccount, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttrString(__pyx_v_m, S_TradingAccountPasswordUpdate); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 28; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_v_fa); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 28; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_TradingAccountPasswordUpdate);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_TradingAccountPasswordUpdate, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttrString(__pyx_v_m, S_TradingCode); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_v_fa); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_TradingCode);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_TradingCode, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetAttrString(__pyx_v_m, S_UserLogout); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetAttr(__pyx_t_2, __pyx_v_fa); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_UserLogout);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_UserLogout, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetAttrString(__pyx_v_m, S_UserPasswordUpdate); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 31; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetAttr(__pyx_t_1, __pyx_v_fa); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 31; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_3lts_10_TraderApi_ApiStruct_UserPasswordUpdate);
  __Pyx_DECREF_SET(__pyx_v_3lts_10_TraderApi_ApiStruct_UserPasswordUpdate, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("lts._TraderApi._init", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_fa);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static void __pyx_f_3lts_10_TraderApi_TraderApi_Release(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("TraderApi_Release", 0);
  ReleaseTraderApi(__pyx_v_self->api, __pyx_v_self->spi);
  __pyx_v_self->api = NULL;
  __pyx_v_self->spi = NULL;
  __Pyx_RefNannyFinishContext();
}
static void __pyx_pw_3lts_10_TraderApi_9TraderApi_1__dealloc__(PyObject *__pyx_v_self); 
static void __pyx_pw_3lts_10_TraderApi_9TraderApi_1__dealloc__(PyObject *__pyx_v_self) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__dealloc__ (wrapper)", 0);
  __pyx_pf_3lts_10_TraderApi_9TraderApi___dealloc__(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
}
static void __pyx_pf_3lts_10_TraderApi_9TraderApi___dealloc__(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__dealloc__", 0);
  __pyx_f_3lts_10_TraderApi_TraderApi_Release(__pyx_v_self);
  __Pyx_RefNannyFinishContext();
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_3Alive(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_3Alive(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("Alive (wrapper)", 0);
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_2Alive(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_2Alive(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("Alive", 0);
  __pyx_t_1 = ((__pyx_v_self->spi != NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_2 = __Pyx_PyInt_From_long(__pyx_v_self->spi->tid); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 48; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_r = __pyx_t_2;
    __pyx_t_2 = 0;
    goto __pyx_L0;
  }
  __pyx_t_1 = ((__pyx_v_self->api != NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __Pyx_INCREF(Py_False);
    __pyx_r = Py_False;
    goto __pyx_L0;
  }
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.Alive", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_5Create(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_5Create(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  const char *__pyx_v_pszFlowPath;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("Create (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pszFlowPath,0};
    PyObject* values[1] = {0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pszFlowPath);
          if (value) { values[0] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "Create") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 51; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    if (values[0]) {
      __pyx_v_pszFlowPath = __Pyx_PyObject_AsString(values[0]); if (unlikely((!__pyx_v_pszFlowPath) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 51; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
    } else {
      __pyx_v_pszFlowPath = ((const char *)__pyx_k_);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("Create", 0, 0, 1, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 51; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.Create", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_4Create(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pszFlowPath);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_4Create(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, const char *__pyx_v_pszFlowPath) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  CSecurityFtdcTraderApi *__pyx_t_2;
  int __pyx_t_3;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("Create", 0);
  __pyx_t_1 = ((__pyx_v_self->api != NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  try {
    __pyx_t_2 = CSecurityFtdcTraderApi::CreateFtdcTraderApi(__pyx_v_pszFlowPath);
  } catch(...) {
    __Pyx_CppExn2PyErr();
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_v_self->api = __pyx_t_2;
  __pyx_t_3 = CheckMemory(__pyx_v_self->api); if (unlikely(__pyx_t_3 == 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 54; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.Create", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_7Release(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_7Release(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("Release (wrapper)", 0);
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_6Release(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_6Release(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("Release", 0);
  __pyx_f_3lts_10_TraderApi_TraderApi_Release(__pyx_v_self);
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_9Init(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_9Init(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("Init (wrapper)", 0);
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_8Init(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_8Init(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("Init", 0);
  __pyx_t_1 = ((__pyx_v_self->api == NULL) != 0);
  if (!__pyx_t_1) {
    __pyx_t_2 = ((__pyx_v_self->spi != NULL) != 0);
    __pyx_t_3 = __pyx_t_2;
  } else {
    __pyx_t_3 = __pyx_t_1;
  }
  if (__pyx_t_3) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_v_self->spi = new CTraderSpi(((PyObject *)__pyx_v_self));
  __pyx_t_4 = CheckMemory(__pyx_v_self->spi); if (unlikely(__pyx_t_4 == 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 62; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_v_self->api->RegisterSpi(__pyx_v_self->spi);
  __pyx_v_self->api->Init();
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.Init", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_11Join(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_11Join(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("Join (wrapper)", 0);
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_10Join(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_10Join(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self) {
  int __pyx_v_ret;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("Join", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_ret = __pyx_v_self->api->Join();
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = __Pyx_PyInt_From_int(__pyx_v_ret); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 70; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.Join", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_13GetTradingDay(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_13GetTradingDay(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("GetTradingDay (wrapper)", 0);
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_12GetTradingDay(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_12GetTradingDay(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self) {
  const char *__pyx_v_ret;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("GetTradingDay", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_ret = __pyx_v_self->api->GetTradingDay();
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = __Pyx_PyBytes_FromString(__pyx_v_ret); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 76; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.GetTradingDay", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_15RegisterFront(PyObject *__pyx_v_self, PyObject *__pyx_arg_pszFrontAddress); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_15RegisterFront(PyObject *__pyx_v_self, PyObject *__pyx_arg_pszFrontAddress) {
  char *__pyx_v_pszFrontAddress;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("RegisterFront (wrapper)", 0);
  assert(__pyx_arg_pszFrontAddress); {
    __pyx_v_pszFrontAddress = __Pyx_PyObject_AsString(__pyx_arg_pszFrontAddress); if (unlikely((!__pyx_v_pszFrontAddress) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 78; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.RegisterFront", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_14RegisterFront(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), ((char *)__pyx_v_pszFrontAddress));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_14RegisterFront(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, char *__pyx_v_pszFrontAddress) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("RegisterFront", 0);
  __pyx_t_1 = ((__pyx_v_self->api == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_v_self->api->RegisterFront(__pyx_v_pszFrontAddress);
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_17SubscribePrivateTopic(PyObject *__pyx_v_self, PyObject *__pyx_arg_nResumeType); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_17SubscribePrivateTopic(PyObject *__pyx_v_self, PyObject *__pyx_arg_nResumeType) {
  enum SECURITY_TE_RESUME_TYPE __pyx_v_nResumeType;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("SubscribePrivateTopic (wrapper)", 0);
  assert(__pyx_arg_nResumeType); {
    __pyx_v_nResumeType = ((enum SECURITY_TE_RESUME_TYPE)PyInt_AsLong(__pyx_arg_nResumeType)); if (unlikely(PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 82; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.SubscribePrivateTopic", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_16SubscribePrivateTopic(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), ((enum SECURITY_TE_RESUME_TYPE)__pyx_v_nResumeType));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_16SubscribePrivateTopic(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, enum SECURITY_TE_RESUME_TYPE __pyx_v_nResumeType) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("SubscribePrivateTopic", 0);
  __pyx_t_1 = ((__pyx_v_self->api == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_v_self->api->SubscribePrivateTopic(__pyx_v_nResumeType);
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_19SubscribePublicTopic(PyObject *__pyx_v_self, PyObject *__pyx_arg_nResumeType); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_19SubscribePublicTopic(PyObject *__pyx_v_self, PyObject *__pyx_arg_nResumeType) {
  enum SECURITY_TE_RESUME_TYPE __pyx_v_nResumeType;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("SubscribePublicTopic (wrapper)", 0);
  assert(__pyx_arg_nResumeType); {
    __pyx_v_nResumeType = ((enum SECURITY_TE_RESUME_TYPE)PyInt_AsLong(__pyx_arg_nResumeType)); if (unlikely(PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 86; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.SubscribePublicTopic", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_18SubscribePublicTopic(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), ((enum SECURITY_TE_RESUME_TYPE)__pyx_v_nResumeType));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_18SubscribePublicTopic(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, enum SECURITY_TE_RESUME_TYPE __pyx_v_nResumeType) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("SubscribePublicTopic", 0);
  __pyx_t_1 = ((__pyx_v_self->api == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_v_self->api->SubscribePublicTopic(__pyx_v_nResumeType);
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_21ReqUserLogin(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_21ReqUserLogin(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pReqUserLogin = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqUserLogin (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pReqUserLogin,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pReqUserLogin)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqUserLogin", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 90; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqUserLogin") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 90; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pReqUserLogin = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 90; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqUserLogin", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 90; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqUserLogin", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_20ReqUserLogin(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pReqUserLogin, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_20ReqUserLogin(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pReqUserLogin, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqUserLogin", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 93; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pReqUserLogin);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pReqUserLogin);
  __Pyx_GIVEREF(__pyx_v_pReqUserLogin);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 93; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 93; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqUserLogin(((struct CSecurityFtdcReqUserLoginField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 95; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqUserLogin", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_23ReqUserLogout(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_23ReqUserLogout(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pUserLogout = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqUserLogout (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pUserLogout,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pUserLogout)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqUserLogout", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqUserLogout") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pUserLogout = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqUserLogout", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqUserLogout", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_22ReqUserLogout(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pUserLogout, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_22ReqUserLogout(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pUserLogout, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqUserLogout", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 100; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pUserLogout);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pUserLogout);
  __Pyx_GIVEREF(__pyx_v_pUserLogout);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 100; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 100; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqUserLogout(((struct CSecurityFtdcUserLogoutField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 102; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqUserLogout", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_25ReqOrderInsert(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_25ReqOrderInsert(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pInputOrder = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqOrderInsert (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pInputOrder,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pInputOrder)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqOrderInsert", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 104; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqOrderInsert") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 104; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pInputOrder = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 104; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqOrderInsert", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 104; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqOrderInsert", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_24ReqOrderInsert(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pInputOrder, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_24ReqOrderInsert(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pInputOrder, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqOrderInsert", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 107; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pInputOrder);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pInputOrder);
  __Pyx_GIVEREF(__pyx_v_pInputOrder);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 107; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 107; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqOrderInsert(((struct CSecurityFtdcInputOrderField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 109; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqOrderInsert", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_27ReqOrderAction(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_27ReqOrderAction(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pInputOrderAction = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqOrderAction (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pInputOrderAction,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pInputOrderAction)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqOrderAction", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 111; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqOrderAction") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 111; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pInputOrderAction = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 111; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqOrderAction", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 111; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqOrderAction", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_26ReqOrderAction(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pInputOrderAction, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_26ReqOrderAction(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pInputOrderAction, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqOrderAction", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 114; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pInputOrderAction);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pInputOrderAction);
  __Pyx_GIVEREF(__pyx_v_pInputOrderAction);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 114; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 114; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqOrderAction(((struct CSecurityFtdcInputOrderActionField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqOrderAction", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_29ReqUserPasswordUpdate(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_29ReqUserPasswordUpdate(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pUserPasswordUpdate = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqUserPasswordUpdate (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pUserPasswordUpdate,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pUserPasswordUpdate)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqUserPasswordUpdate", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 118; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqUserPasswordUpdate") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 118; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pUserPasswordUpdate = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 118; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqUserPasswordUpdate", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 118; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqUserPasswordUpdate", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_28ReqUserPasswordUpdate(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pUserPasswordUpdate, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_28ReqUserPasswordUpdate(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pUserPasswordUpdate, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqUserPasswordUpdate", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 121; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pUserPasswordUpdate);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pUserPasswordUpdate);
  __Pyx_GIVEREF(__pyx_v_pUserPasswordUpdate);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 121; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 121; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqUserPasswordUpdate(((struct CSecurityFtdcUserPasswordUpdateField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 123; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqUserPasswordUpdate", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_31ReqTradingAccountPasswordUpdate(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_31ReqTradingAccountPasswordUpdate(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pTradingAccountPasswordUpdate = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqTradingAccountPasswordUpdate (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pTradingAccountPasswordUpdate,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pTradingAccountPasswordUpdate)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqTradingAccountPasswordUpdate", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 125; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqTradingAccountPasswordUpdate") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 125; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pTradingAccountPasswordUpdate = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 125; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqTradingAccountPasswordUpdate", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 125; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqTradingAccountPasswordUpdate", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_30ReqTradingAccountPasswordUpdate(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pTradingAccountPasswordUpdate, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_30ReqTradingAccountPasswordUpdate(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pTradingAccountPasswordUpdate, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqTradingAccountPasswordUpdate", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 128; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pTradingAccountPasswordUpdate);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pTradingAccountPasswordUpdate);
  __Pyx_GIVEREF(__pyx_v_pTradingAccountPasswordUpdate);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 128; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 128; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqTradingAccountPasswordUpdate(((struct CSecurityFtdcTradingAccountPasswordUpdateField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 130; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqTradingAccountPasswordUpdate", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_33ReqQryExchange(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_33ReqQryExchange(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryExchange = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryExchange (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryExchange,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryExchange)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryExchange", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 132; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryExchange") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 132; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryExchange = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 132; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryExchange", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 132; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryExchange", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_32ReqQryExchange(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryExchange, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_32ReqQryExchange(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryExchange, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryExchange", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 135; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryExchange);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryExchange);
  __Pyx_GIVEREF(__pyx_v_pQryExchange);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 135; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 135; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryExchange(((struct CSecurityFtdcQryExchangeField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 137; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryExchange", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_35ReqQryInstrument(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_35ReqQryInstrument(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryInstrument = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryInstrument (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryInstrument,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryInstrument)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryInstrument", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryInstrument") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryInstrument = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryInstrument", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryInstrument", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_34ReqQryInstrument(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryInstrument, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_34ReqQryInstrument(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryInstrument, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryInstrument", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryInstrument);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryInstrument);
  __Pyx_GIVEREF(__pyx_v_pQryInstrument);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryInstrument(((struct CSecurityFtdcQryInstrumentField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 144; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryInstrument", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_37ReqQryInvestor(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_37ReqQryInvestor(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryInvestor = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryInvestor (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryInvestor,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryInvestor)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryInvestor", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 146; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryInvestor") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 146; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryInvestor = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 146; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryInvestor", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 146; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryInvestor", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_36ReqQryInvestor(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryInvestor, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_36ReqQryInvestor(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryInvestor, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryInvestor", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 149; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryInvestor);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryInvestor);
  __Pyx_GIVEREF(__pyx_v_pQryInvestor);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 149; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 149; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryInvestor(((struct CSecurityFtdcQryInvestorField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 151; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryInvestor", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_39ReqQryTradingCode(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_39ReqQryTradingCode(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryTradingCode = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryTradingCode (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryTradingCode,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryTradingCode)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryTradingCode", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 153; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryTradingCode") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 153; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryTradingCode = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 153; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryTradingCode", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 153; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryTradingCode", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_38ReqQryTradingCode(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryTradingCode, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_38ReqQryTradingCode(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryTradingCode, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryTradingCode", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 156; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryTradingCode);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryTradingCode);
  __Pyx_GIVEREF(__pyx_v_pQryTradingCode);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 156; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 156; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryTradingCode(((struct CSecurityFtdcQryTradingCodeField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryTradingCode", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_41ReqQryTradingAccount(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_41ReqQryTradingAccount(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryTradingAccount = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryTradingAccount (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryTradingAccount,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryTradingAccount)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryTradingAccount", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 160; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryTradingAccount") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 160; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryTradingAccount = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 160; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryTradingAccount", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 160; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryTradingAccount", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_40ReqQryTradingAccount(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryTradingAccount, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_40ReqQryTradingAccount(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryTradingAccount, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryTradingAccount", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 163; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryTradingAccount);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryTradingAccount);
  __Pyx_GIVEREF(__pyx_v_pQryTradingAccount);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 163; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 163; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryTradingAccount(((struct CSecurityFtdcQryTradingAccountField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 165; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryTradingAccount", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_43ReqQryDepthMarketData(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_43ReqQryDepthMarketData(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryDepthMarketData = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryDepthMarketData (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryDepthMarketData,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryDepthMarketData)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryDepthMarketData", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryDepthMarketData") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryDepthMarketData = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryDepthMarketData", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryDepthMarketData", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_42ReqQryDepthMarketData(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryDepthMarketData, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_42ReqQryDepthMarketData(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryDepthMarketData, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryDepthMarketData", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 170; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryDepthMarketData);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryDepthMarketData);
  __Pyx_GIVEREF(__pyx_v_pQryDepthMarketData);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 170; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 170; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryDepthMarketData(((struct CSecurityFtdcQryDepthMarketDataField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 172; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryDepthMarketData", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_45ReqQryBondInterest(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_45ReqQryBondInterest(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryBondInterest = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryBondInterest (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryBondInterest,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryBondInterest)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryBondInterest", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 174; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryBondInterest") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 174; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryBondInterest = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 174; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryBondInterest", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 174; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryBondInterest", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_44ReqQryBondInterest(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryBondInterest, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_44ReqQryBondInterest(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryBondInterest, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryBondInterest", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 177; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryBondInterest);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryBondInterest);
  __Pyx_GIVEREF(__pyx_v_pQryBondInterest);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 177; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 177; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryBondInterest(((struct CSecurityFtdcQryBondInterestField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 179; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryBondInterest", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_47ReqQryMarketRationInfo(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_47ReqQryMarketRationInfo(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryMarketRationInfo = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryMarketRationInfo (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryMarketRationInfo,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryMarketRationInfo)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryMarketRationInfo", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 181; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryMarketRationInfo") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 181; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryMarketRationInfo = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 181; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryMarketRationInfo", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 181; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryMarketRationInfo", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_46ReqQryMarketRationInfo(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryMarketRationInfo, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_46ReqQryMarketRationInfo(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryMarketRationInfo, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryMarketRationInfo", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 184; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryMarketRationInfo);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryMarketRationInfo);
  __Pyx_GIVEREF(__pyx_v_pQryMarketRationInfo);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 184; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 184; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryMarketRationInfo(((struct CSecurityFtdcQryMarketRationInfoField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 186; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryMarketRationInfo", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_49ReqQryInstrumentCommissionRate(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_49ReqQryInstrumentCommissionRate(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryInstrumentCommissionRate = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryInstrumentCommissionRate (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryInstrumentCommissionRate,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryInstrumentCommissionRate)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryInstrumentCommissionRate", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 188; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryInstrumentCommissionRate") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 188; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryInstrumentCommissionRate = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 188; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryInstrumentCommissionRate", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 188; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryInstrumentCommissionRate", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_48ReqQryInstrumentCommissionRate(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryInstrumentCommissionRate, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_48ReqQryInstrumentCommissionRate(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryInstrumentCommissionRate, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryInstrumentCommissionRate", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 191; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryInstrumentCommissionRate);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryInstrumentCommissionRate);
  __Pyx_GIVEREF(__pyx_v_pQryInstrumentCommissionRate);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 191; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 191; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryInstrumentCommissionRate(((struct CSecurityFtdcQryInstrumentCommissionRateField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 193; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryInstrumentCommissionRate", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_51ReqQryOrder(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_51ReqQryOrder(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryOrder = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryOrder (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryOrder,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryOrder)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryOrder", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 195; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryOrder") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 195; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryOrder = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 195; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryOrder", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 195; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryOrder", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_50ReqQryOrder(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryOrder, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_50ReqQryOrder(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryOrder, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryOrder", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 198; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryOrder);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryOrder);
  __Pyx_GIVEREF(__pyx_v_pQryOrder);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 198; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 198; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryOrder(((struct CSecurityFtdcQryOrderField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 200; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryOrder", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_53ReqQryTrade(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_53ReqQryTrade(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryTrade = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryTrade (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryTrade,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryTrade)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryTrade", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 202; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryTrade") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 202; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryTrade = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 202; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryTrade", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 202; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryTrade", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_52ReqQryTrade(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryTrade, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_52ReqQryTrade(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryTrade, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryTrade", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 205; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryTrade);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryTrade);
  __Pyx_GIVEREF(__pyx_v_pQryTrade);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 205; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 205; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryTrade(((struct CSecurityFtdcQryTradeField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 207; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryTrade", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_55ReqQryInvestorPosition(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_55ReqQryInvestorPosition(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryInvestorPosition = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryInvestorPosition (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryInvestorPosition,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryInvestorPosition)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryInvestorPosition", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 209; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryInvestorPosition") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 209; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryInvestorPosition = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 209; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryInvestorPosition", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 209; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryInvestorPosition", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_54ReqQryInvestorPosition(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryInvestorPosition, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_54ReqQryInvestorPosition(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryInvestorPosition, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryInvestorPosition", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryInvestorPosition);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryInvestorPosition);
  __Pyx_GIVEREF(__pyx_v_pQryInvestorPosition);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryInvestorPosition(((struct CSecurityFtdcQryInvestorPositionField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 214; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryInvestorPosition", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_57ReqFundOutByLiber(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_57ReqFundOutByLiber(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pInputFundTransfer = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqFundOutByLiber (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pInputFundTransfer,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pInputFundTransfer)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqFundOutByLiber", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 216; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqFundOutByLiber") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 216; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pInputFundTransfer = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 216; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqFundOutByLiber", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 216; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqFundOutByLiber", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_56ReqFundOutByLiber(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pInputFundTransfer, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_56ReqFundOutByLiber(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pInputFundTransfer, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqFundOutByLiber", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pInputFundTransfer);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pInputFundTransfer);
  __Pyx_GIVEREF(__pyx_v_pInputFundTransfer);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqFundOutByLiber(((struct CSecurityFtdcInputFundTransferField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 221; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqFundOutByLiber", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_59ReqQryFundTransferSerial(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); 
static PyObject *__pyx_pw_3lts_10_TraderApi_9TraderApi_59ReqQryFundTransferSerial(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pQryFundTransferSerial = 0;
  int __pyx_v_nRequestID;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("ReqQryFundTransferSerial (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pQryFundTransferSerial,&__pyx_n_s_nRequestID,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case 1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case 0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_pQryFundTransferSerial)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case 1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_nRequestID)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("ReqQryFundTransferSerial", 1, 2, 2, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "ReqQryFundTransferSerial") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_pQryFundTransferSerial = values[0];
    __pyx_v_nRequestID = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_nRequestID == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("ReqQryFundTransferSerial", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryFundTransferSerial", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3lts_10_TraderApi_9TraderApi_58ReqQryFundTransferSerial(((struct __pyx_obj_3lts_10_TraderApi_TraderApi *)__pyx_v_self), __pyx_v_pQryFundTransferSerial, __pyx_v_nRequestID);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_pf_3lts_10_TraderApi_9TraderApi_58ReqQryFundTransferSerial(struct __pyx_obj_3lts_10_TraderApi_TraderApi *__pyx_v_self, PyObject *__pyx_v_pQryFundTransferSerial, int __pyx_v_nRequestID) {
  size_t __pyx_v_address;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  size_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("ReqQryFundTransferSerial", 0);
  __pyx_t_1 = ((__pyx_v_self->spi == NULL) != 0);
  if (__pyx_t_1) {
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;
  }
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 226; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_pQryFundTransferSerial);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_pQryFundTransferSerial);
  __Pyx_GIVEREF(__pyx_v_pQryFundTransferSerial);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_addressof, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 226; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_size_t(__pyx_t_3); if (unlikely((__pyx_t_4 == (size_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 226; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_address = __pyx_t_4;
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      #endif
      {
        __pyx_v_nRequestID = __pyx_v_self->api->ReqQryFundTransferSerial(((struct CSecurityFtdcQryFundTransferSerialField *)__pyx_v_address), __pyx_v_nRequestID);
      }
      {
        {
          #ifdef WITH_THREAD
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L6;
        }
        __pyx_L6:;
      }
  }
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 228; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderApi.ReqQryFundTransferSerial", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnFrontConnected(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnFrontConnected", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnFrontConnected); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 232; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_empty_tuple, NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 232; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnFrontConnected", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnFrontDisconnected(PyObject *__pyx_v_self, int __pyx_v_nReason) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnFrontDisconnected", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnFrontDisconnected); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 236; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyInt_From_int(__pyx_v_nReason); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 236; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 236; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 236; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnFrontDisconnected", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnHeartBeatWarning(PyObject *__pyx_v_self, int __pyx_v_nTimeLapse) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnHeartBeatWarning", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnHeartBeatWarning); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 240; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyInt_From_int(__pyx_v_nTimeLapse); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 240; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 240; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 240; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnHeartBeatWarning", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspError(PyObject *__pyx_v_self, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspError", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspError); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyTuple_New(3); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspError", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspUserLogin(PyObject *__pyx_v_self, struct CSecurityFtdcRspUserLoginField *__pyx_v_pRspUserLogin, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspUserLogin", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspUserLogin); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pRspUserLogin == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspUserLogin)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspUserLogin, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 248; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspUserLogin", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspUserLogout(PyObject *__pyx_v_self, struct CSecurityFtdcUserLogoutField *__pyx_v_pUserLogout, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspUserLogout", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspUserLogout); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pUserLogout == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pUserLogout)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_UserLogout, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 252; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspUserLogout", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspOrderInsert(PyObject *__pyx_v_self, struct CSecurityFtdcInputOrderField *__pyx_v_pInputOrder, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspOrderInsert", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspOrderInsert); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pInputOrder == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pInputOrder)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_InputOrder, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspOrderInsert", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspOrderAction(PyObject *__pyx_v_self, struct CSecurityFtdcInputOrderActionField *__pyx_v_pInputOrderAction, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspOrderAction", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspOrderAction); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pInputOrderAction == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pInputOrderAction)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_InputOrderAction, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspOrderAction", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspUserPasswordUpdate(PyObject *__pyx_v_self, struct CSecurityFtdcUserPasswordUpdateField *__pyx_v_pUserPasswordUpdate, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspUserPasswordUpdate", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspUserPasswordUpdate); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pUserPasswordUpdate == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pUserPasswordUpdate)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_UserPasswordUpdate, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspUserPasswordUpdate", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspTradingAccountPasswordUpdate(PyObject *__pyx_v_self, struct CSecurityFtdcTradingAccountPasswordUpdateField *__pyx_v_pTradingAccountPasswordUpdate, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspTradingAccountPasswordUpdate", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspTradingAccountPasswordUpdat); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pTradingAccountPasswordUpdate == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pTradingAccountPasswordUpdate)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_TradingAccountPasswordUpdate, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspTradingAccountPasswordUpdate", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryExchange(PyObject *__pyx_v_self, struct CSecurityFtdcExchangeField *__pyx_v_pExchange, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryExchange", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryExchange); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pExchange == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pExchange)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_Exchange, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryExchange", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryInstrument(PyObject *__pyx_v_self, struct CSecurityFtdcInstrumentField *__pyx_v_pInstrument, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryInstrument", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryInstrument); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pInstrument == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pInstrument)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_Instrument, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryInstrument", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryInvestor(PyObject *__pyx_v_self, struct CSecurityFtdcInvestorField *__pyx_v_pInvestor, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryInvestor", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryInvestor); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pInvestor == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pInvestor)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_Investor, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryInvestor", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryTradingCode(PyObject *__pyx_v_self, struct CSecurityFtdcTradingCodeField *__pyx_v_pTradingCode, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryTradingCode", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryTradingCode); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pTradingCode == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pTradingCode)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_TradingCode, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryTradingCode", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryTradingAccount(PyObject *__pyx_v_self, struct CSecurityFtdcTradingAccountField *__pyx_v_pTradingAccount, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryTradingAccount", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryTradingAccount); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 288; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pTradingAccount == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pTradingAccount)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 288; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 288; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_TradingAccount, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 288; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 288; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 288; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 288; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 288; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 288; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 288; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 288; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryTradingAccount", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryDepthMarketData(PyObject *__pyx_v_self, struct CSecurityFtdcDepthMarketDataField *__pyx_v_pDepthMarketData, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryDepthMarketData", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryDepthMarketData); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pDepthMarketData == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pDepthMarketData)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_DepthMarketData, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryDepthMarketData", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryBondInterest(PyObject *__pyx_v_self, struct CSecurityFtdcBondInterestField *__pyx_v_pBondInterest, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryBondInterest", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryBondInterest); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pBondInterest == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pBondInterest)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_BondInterest, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryBondInterest", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryMarketRationInfo(PyObject *__pyx_v_self, struct CSecurityFtdcMarketRationInfoField *__pyx_v_pMarketRationInfo, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryMarketRationInfo", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryMarketRationInfo); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pMarketRationInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pMarketRationInfo)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_MarketRationInfo, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryMarketRationInfo", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryInstrumentCommissionRate(PyObject *__pyx_v_self, struct CSecurityFtdcInstrumentCommissionRateField *__pyx_v_pInstrumentCommissionRate, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryInstrumentCommissionRate", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryInstrumentCommissionRate); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pInstrumentCommissionRate == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pInstrumentCommissionRate)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_InstrumentCommissionRate, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryInstrumentCommissionRate", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryOrder(PyObject *__pyx_v_self, struct CSecurityFtdcOrderField *__pyx_v_pOrder, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryOrder", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryOrder); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pOrder == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pOrder)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_Order, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryOrder", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryTrade(PyObject *__pyx_v_self, struct CSecurityFtdcTradeField *__pyx_v_pTrade, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryTrade", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryTrade); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pTrade == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pTrade)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_Trade, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 312; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryTrade", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryInvestorPosition(PyObject *__pyx_v_self, struct CSecurityFtdcInvestorPositionField *__pyx_v_pInvestorPosition, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryInvestorPosition", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryInvestorPosition); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pInvestorPosition == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pInvestorPosition)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_InvestorPosition, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 316; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryInvestorPosition", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRtnOrder(PyObject *__pyx_v_self, struct CSecurityFtdcOrderField *__pyx_v_pOrder) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRtnOrder", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRtnOrder); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 320; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pOrder == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pOrder)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 320; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 320; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_Order, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 320; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 320; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 320; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRtnOrder", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRtnTrade(PyObject *__pyx_v_self, struct CSecurityFtdcTradeField *__pyx_v_pTrade) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRtnTrade", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRtnTrade); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pTrade == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pTrade)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_Trade, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 324; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRtnTrade", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnErrRtnOrderInsert(PyObject *__pyx_v_self, struct CSecurityFtdcInputOrderField *__pyx_v_pInputOrder, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnErrRtnOrderInsert", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnErrRtnOrderInsert); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pInputOrder == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pInputOrder)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_InputOrder, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 328; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnErrRtnOrderInsert", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnErrRtnOrderAction(PyObject *__pyx_v_self, struct CSecurityFtdcOrderActionField *__pyx_v_pOrderAction, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnErrRtnOrderAction", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnErrRtnOrderAction); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pOrderAction == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pOrderAction)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_OrderAction, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 332; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnErrRtnOrderAction", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspFundOutByLiber(PyObject *__pyx_v_self, struct CSecurityFtdcInputFundTransferField *__pyx_v_pInputFundTransfer, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspFundOutByLiber", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspFundOutByLiber); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 336; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pInputFundTransfer == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pInputFundTransfer)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 336; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 336; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_InputFundTransfer, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 336; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 336; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 336; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 336; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 336; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 336; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 336; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 336; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspFundOutByLiber", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRtnFundOutByLiber(PyObject *__pyx_v_self, struct CSecurityFtdcFundTransferField *__pyx_v_pFundTransfer) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRtnFundOutByLiber", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRtnFundOutByLiber); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 340; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pFundTransfer == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pFundTransfer)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 340; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 340; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_FundTransfer, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 340; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 340; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 340; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRtnFundOutByLiber", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnErrRtnFundOutByLiber(PyObject *__pyx_v_self, struct CSecurityFtdcInputFundTransferField *__pyx_v_pInputFundTransfer, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnErrRtnFundOutByLiber", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnErrRtnFundOutByLiber); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 344; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pInputFundTransfer == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pInputFundTransfer)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 344; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 344; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_InputFundTransfer, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 344; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 344; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 344; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 344; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 344; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 344; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnErrRtnFundOutByLiber", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRtnFundInByBank(PyObject *__pyx_v_self, struct CSecurityFtdcFundTransferField *__pyx_v_pFundTransfer) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRtnFundInByBank", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRtnFundInByBank); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 348; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pFundTransfer == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pFundTransfer)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 348; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 348; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_FundTransfer, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 348; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 348; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 348; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRtnFundInByBank", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
int TraderSpi_OnRspQryFundTransferSerial(PyObject *__pyx_v_self, struct CSecurityFtdcFundTransferField *__pyx_v_pFundTransfer, struct CSecurityFtdcRspInfoField *__pyx_v_pRspInfo, int __pyx_v_nRequestID, bool __pyx_v_bIsLast) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("TraderSpi_OnRspQryFundTransferSerial", 0);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_OnRspQryFundTransferSerial); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (((__pyx_v_pFundTransfer == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_2 = Py_None;
  } else {
    __pyx_t_3 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pFundTransfer)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_FundTransfer, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_2 = __pyx_t_3;
    __pyx_t_3 = 0;
  }
  if (((__pyx_v_pRspInfo == NULL) != 0)) {
    __Pyx_INCREF(Py_None);
    __pyx_t_3 = Py_None;
  } else {
    __pyx_t_4 = __Pyx_PyInt_FromSize_t(((size_t)__pyx_v_pRspInfo)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_nRequestID); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_bIsLast); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = PyTuple_New(4); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 352; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("lts._TraderApi.TraderSpi_OnRspQryFundTransferSerial", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static PyObject *__pyx_tp_new_3lts_10_TraderApi_TraderApi(PyTypeObject *t, CYTHON_UNUSED PyObject *a, CYTHON_UNUSED PyObject *k) {
  PyObject *o;
  if (likely((t->tp_flags & Py_TPFLAGS_IS_ABSTRACT) == 0)) {
    o = (*t->tp_alloc)(t, 0);
  } else {
    o = (PyObject *) PyBaseObject_Type.tp_new(t, __pyx_empty_tuple, 0);
  }
  if (unlikely(!o)) return 0;
  return o;
}
static void __pyx_tp_dealloc_3lts_10_TraderApi_TraderApi(PyObject *o) {
  #if PY_VERSION_HEX >= 0x030400a1
  if (unlikely(Py_TYPE(o)->tp_finalize) && (!PyType_IS_GC(Py_TYPE(o)) || !_PyGC_FINALIZED(o))) {
    if (PyObject_CallFinalizerFromDealloc(o)) return;
  }
  #endif
  {
    PyObject *etype, *eval, *etb;
    PyErr_Fetch(&etype, &eval, &etb);
    ++Py_REFCNT(o);
    __pyx_pw_3lts_10_TraderApi_9TraderApi_1__dealloc__(o);
    --Py_REFCNT(o);
    PyErr_Restore(etype, eval, etb);
  }
  (*Py_TYPE(o)->tp_free)(o);
}
static PyMethodDef __pyx_methods_3lts_10_TraderApi_TraderApi[] = {
  {__Pyx_NAMESTR("Alive"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_3Alive, METH_NOARGS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("Create"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_5Create, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("Release"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_7Release, METH_NOARGS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("Init"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_9Init, METH_NOARGS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("Join"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_11Join, METH_NOARGS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("GetTradingDay"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_13GetTradingDay, METH_NOARGS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("RegisterFront"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_15RegisterFront, METH_O, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("SubscribePrivateTopic"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_17SubscribePrivateTopic, METH_O, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("SubscribePublicTopic"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_19SubscribePublicTopic, METH_O, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqUserLogin"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_21ReqUserLogin, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqUserLogout"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_23ReqUserLogout, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqOrderInsert"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_25ReqOrderInsert, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqOrderAction"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_27ReqOrderAction, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqUserPasswordUpdate"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_29ReqUserPasswordUpdate, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqTradingAccountPasswordUpdate"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_31ReqTradingAccountPasswordUpdate, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryExchange"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_33ReqQryExchange, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryInstrument"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_35ReqQryInstrument, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryInvestor"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_37ReqQryInvestor, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryTradingCode"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_39ReqQryTradingCode, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryTradingAccount"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_41ReqQryTradingAccount, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryDepthMarketData"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_43ReqQryDepthMarketData, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryBondInterest"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_45ReqQryBondInterest, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryMarketRationInfo"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_47ReqQryMarketRationInfo, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryInstrumentCommissionRate"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_49ReqQryInstrumentCommissionRate, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryOrder"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_51ReqQryOrder, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryTrade"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_53ReqQryTrade, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryInvestorPosition"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_55ReqQryInvestorPosition, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqFundOutByLiber"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_57ReqFundOutByLiber, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {__Pyx_NAMESTR("ReqQryFundTransferSerial"), (PyCFunction)__pyx_pw_3lts_10_TraderApi_9TraderApi_59ReqQryFundTransferSerial, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {0, 0, 0, 0}
};
static PyTypeObject __pyx_type_3lts_10_TraderApi_TraderApi = {
  PyVarObject_HEAD_INIT(0, 0)
  __Pyx_NAMESTR("lts._TraderApi.TraderApi"), 
  sizeof(struct __pyx_obj_3lts_10_TraderApi_TraderApi), 
  0, 
  __pyx_tp_dealloc_3lts_10_TraderApi_TraderApi, 
  0, 
  0, 
  0, 
  #if PY_MAJOR_VERSION < 3
  0, 
  #else
  0, 
  #endif
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  __pyx_methods_3lts_10_TraderApi_TraderApi, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  __pyx_tp_new_3lts_10_TraderApi_TraderApi, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  #if PY_VERSION_HEX >= 0x02060000
  0, 
  #endif
  #if PY_VERSION_HEX >= 0x030400a1
  0, 
  #endif
};
static PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};
#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef __pyx_moduledef = {
  #if PY_VERSION_HEX < 0x03020000
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL },
  #else
    PyModuleDef_HEAD_INIT,
  #endif
    __Pyx_NAMESTR("_TraderApi"),
    0, 
    -1, 
    __pyx_methods ,
    NULL, 
    NULL, 
    NULL, 
    NULL 
};
#endif
static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_n_s_OnErrRtnFundOutByLiber, __pyx_k_OnErrRtnFundOutByLiber, sizeof(__pyx_k_OnErrRtnFundOutByLiber), 0, 0, 1, 1},
  {&__pyx_n_s_OnErrRtnOrderAction, __pyx_k_OnErrRtnOrderAction, sizeof(__pyx_k_OnErrRtnOrderAction), 0, 0, 1, 1},
  {&__pyx_n_s_OnErrRtnOrderInsert, __pyx_k_OnErrRtnOrderInsert, sizeof(__pyx_k_OnErrRtnOrderInsert), 0, 0, 1, 1},
  {&__pyx_n_s_OnFrontConnected, __pyx_k_OnFrontConnected, sizeof(__pyx_k_OnFrontConnected), 0, 0, 1, 1},
  {&__pyx_n_s_OnFrontDisconnected, __pyx_k_OnFrontDisconnected, sizeof(__pyx_k_OnFrontDisconnected), 0, 0, 1, 1},
  {&__pyx_n_s_OnHeartBeatWarning, __pyx_k_OnHeartBeatWarning, sizeof(__pyx_k_OnHeartBeatWarning), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspError, __pyx_k_OnRspError, sizeof(__pyx_k_OnRspError), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspFundOutByLiber, __pyx_k_OnRspFundOutByLiber, sizeof(__pyx_k_OnRspFundOutByLiber), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspOrderAction, __pyx_k_OnRspOrderAction, sizeof(__pyx_k_OnRspOrderAction), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspOrderInsert, __pyx_k_OnRspOrderInsert, sizeof(__pyx_k_OnRspOrderInsert), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryBondInterest, __pyx_k_OnRspQryBondInterest, sizeof(__pyx_k_OnRspQryBondInterest), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryDepthMarketData, __pyx_k_OnRspQryDepthMarketData, sizeof(__pyx_k_OnRspQryDepthMarketData), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryExchange, __pyx_k_OnRspQryExchange, sizeof(__pyx_k_OnRspQryExchange), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryFundTransferSerial, __pyx_k_OnRspQryFundTransferSerial, sizeof(__pyx_k_OnRspQryFundTransferSerial), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryInstrument, __pyx_k_OnRspQryInstrument, sizeof(__pyx_k_OnRspQryInstrument), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryInstrumentCommissionRate, __pyx_k_OnRspQryInstrumentCommissionRate, sizeof(__pyx_k_OnRspQryInstrumentCommissionRate), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryInvestor, __pyx_k_OnRspQryInvestor, sizeof(__pyx_k_OnRspQryInvestor), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryInvestorPosition, __pyx_k_OnRspQryInvestorPosition, sizeof(__pyx_k_OnRspQryInvestorPosition), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryMarketRationInfo, __pyx_k_OnRspQryMarketRationInfo, sizeof(__pyx_k_OnRspQryMarketRationInfo), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryOrder, __pyx_k_OnRspQryOrder, sizeof(__pyx_k_OnRspQryOrder), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryTrade, __pyx_k_OnRspQryTrade, sizeof(__pyx_k_OnRspQryTrade), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryTradingAccount, __pyx_k_OnRspQryTradingAccount, sizeof(__pyx_k_OnRspQryTradingAccount), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspQryTradingCode, __pyx_k_OnRspQryTradingCode, sizeof(__pyx_k_OnRspQryTradingCode), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspTradingAccountPasswordUpdat, __pyx_k_OnRspTradingAccountPasswordUpdat, sizeof(__pyx_k_OnRspTradingAccountPasswordUpdat), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspUserLogin, __pyx_k_OnRspUserLogin, sizeof(__pyx_k_OnRspUserLogin), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspUserLogout, __pyx_k_OnRspUserLogout, sizeof(__pyx_k_OnRspUserLogout), 0, 0, 1, 1},
  {&__pyx_n_s_OnRspUserPasswordUpdate, __pyx_k_OnRspUserPasswordUpdate, sizeof(__pyx_k_OnRspUserPasswordUpdate), 0, 0, 1, 1},
  {&__pyx_n_s_OnRtnFundInByBank, __pyx_k_OnRtnFundInByBank, sizeof(__pyx_k_OnRtnFundInByBank), 0, 0, 1, 1},
  {&__pyx_n_s_OnRtnFundOutByLiber, __pyx_k_OnRtnFundOutByLiber, sizeof(__pyx_k_OnRtnFundOutByLiber), 0, 0, 1, 1},
  {&__pyx_n_s_OnRtnOrder, __pyx_k_OnRtnOrder, sizeof(__pyx_k_OnRtnOrder), 0, 0, 1, 1},
  {&__pyx_n_s_OnRtnTrade, __pyx_k_OnRtnTrade, sizeof(__pyx_k_OnRtnTrade), 0, 0, 1, 1},
  {&__pyx_n_s_main, __pyx_k_main, sizeof(__pyx_k_main), 0, 0, 1, 1},
  {&__pyx_n_s_nRequestID, __pyx_k_nRequestID, sizeof(__pyx_k_nRequestID), 0, 0, 1, 1},
  {&__pyx_n_s_pInputFundTransfer, __pyx_k_pInputFundTransfer, sizeof(__pyx_k_pInputFundTransfer), 0, 0, 1, 1},
  {&__pyx_n_s_pInputOrder, __pyx_k_pInputOrder, sizeof(__pyx_k_pInputOrder), 0, 0, 1, 1},
  {&__pyx_n_s_pInputOrderAction, __pyx_k_pInputOrderAction, sizeof(__pyx_k_pInputOrderAction), 0, 0, 1, 1},
  {&__pyx_n_s_pQryBondInterest, __pyx_k_pQryBondInterest, sizeof(__pyx_k_pQryBondInterest), 0, 0, 1, 1},
  {&__pyx_n_s_pQryDepthMarketData, __pyx_k_pQryDepthMarketData, sizeof(__pyx_k_pQryDepthMarketData), 0, 0, 1, 1},
  {&__pyx_n_s_pQryExchange, __pyx_k_pQryExchange, sizeof(__pyx_k_pQryExchange), 0, 0, 1, 1},
  {&__pyx_n_s_pQryFundTransferSerial, __pyx_k_pQryFundTransferSerial, sizeof(__pyx_k_pQryFundTransferSerial), 0, 0, 1, 1},
  {&__pyx_n_s_pQryInstrument, __pyx_k_pQryInstrument, sizeof(__pyx_k_pQryInstrument), 0, 0, 1, 1},
  {&__pyx_n_s_pQryInstrumentCommissionRate, __pyx_k_pQryInstrumentCommissionRate, sizeof(__pyx_k_pQryInstrumentCommissionRate), 0, 0, 1, 1},
  {&__pyx_n_s_pQryInvestor, __pyx_k_pQryInvestor, sizeof(__pyx_k_pQryInvestor), 0, 0, 1, 1},
  {&__pyx_n_s_pQryInvestorPosition, __pyx_k_pQryInvestorPosition, sizeof(__pyx_k_pQryInvestorPosition), 0, 0, 1, 1},
  {&__pyx_n_s_pQryMarketRationInfo, __pyx_k_pQryMarketRationInfo, sizeof(__pyx_k_pQryMarketRationInfo), 0, 0, 1, 1},
  {&__pyx_n_s_pQryOrder, __pyx_k_pQryOrder, sizeof(__pyx_k_pQryOrder), 0, 0, 1, 1},
  {&__pyx_n_s_pQryTrade, __pyx_k_pQryTrade, sizeof(__pyx_k_pQryTrade), 0, 0, 1, 1},
  {&__pyx_n_s_pQryTradingAccount, __pyx_k_pQryTradingAccount, sizeof(__pyx_k_pQryTradingAccount), 0, 0, 1, 1},
  {&__pyx_n_s_pQryTradingCode, __pyx_k_pQryTradingCode, sizeof(__pyx_k_pQryTradingCode), 0, 0, 1, 1},
  {&__pyx_n_s_pReqUserLogin, __pyx_k_pReqUserLogin, sizeof(__pyx_k_pReqUserLogin), 0, 0, 1, 1},
  {&__pyx_n_s_pTradingAccountPasswordUpdate, __pyx_k_pTradingAccountPasswordUpdate, sizeof(__pyx_k_pTradingAccountPasswordUpdate), 0, 0, 1, 1},
  {&__pyx_n_s_pUserLogout, __pyx_k_pUserLogout, sizeof(__pyx_k_pUserLogout), 0, 0, 1, 1},
  {&__pyx_n_s_pUserPasswordUpdate, __pyx_k_pUserPasswordUpdate, sizeof(__pyx_k_pUserPasswordUpdate), 0, 0, 1, 1},
  {&__pyx_n_s_pszFlowPath, __pyx_k_pszFlowPath, sizeof(__pyx_k_pszFlowPath), 0, 0, 1, 1},
  {&__pyx_n_s_test, __pyx_k_test, sizeof(__pyx_k_test), 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}
};
static int __Pyx_InitCachedBuiltins(void) {
  return 0;
}
static int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_InitCachedConstants", 0);
  __Pyx_RefNannyFinishContext();
  return 0;
}
static int __Pyx_InitGlobals(void) {
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  return 0;
  __pyx_L1_error:;
  return -1;
}
#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC init_TraderApi(void); 
PyMODINIT_FUNC init_TraderApi(void)
#else
PyMODINIT_FUNC PyInit__TraderApi(void); 
PyMODINIT_FUNC PyInit__TraderApi(void)
#endif
{
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannyDeclarations
  #if CYTHON_REFNANNY
  __Pyx_RefNanny = __Pyx_RefNannyImportAPI("refnanny");
  if (!__Pyx_RefNanny) {
      PyErr_Clear();
      __Pyx_RefNanny = __Pyx_RefNannyImportAPI("Cython.Runtime.refnanny");
      if (!__Pyx_RefNanny)
          Py_FatalError("failed to import 'refnanny' module");
  }
  #endif
  __Pyx_RefNannySetupContext("PyMODINIT_FUNC PyInit__TraderApi(void)", 0);
  if ( __Pyx_check_binary_version() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_empty_tuple = PyTuple_New(0); if (unlikely(!__pyx_empty_tuple)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_empty_bytes = PyBytes_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_bytes)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #ifdef __Pyx_CyFunction_USED
  if (__Pyx_CyFunction_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  #ifdef __Pyx_FusedFunction_USED
  if (__pyx_FusedFunction_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  #ifdef __Pyx_Generator_USED
  if (__pyx_Generator_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  #if defined(__PYX_FORCE_INIT_THREADS) && __PYX_FORCE_INIT_THREADS
  #ifdef WITH_THREAD 
  PyEval_InitThreads();
  #endif
  #endif
  #if PY_MAJOR_VERSION < 3
  __pyx_m = Py_InitModule4(__Pyx_NAMESTR("_TraderApi"), __pyx_methods, 0, 0, PYTHON_API_VERSION); Py_XINCREF(__pyx_m);
  #else
  __pyx_m = PyModule_Create(&__pyx_moduledef);
  #endif
  if (unlikely(!__pyx_m)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_d = PyModule_GetDict(__pyx_m); if (unlikely(!__pyx_d)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  Py_INCREF(__pyx_d);
  __pyx_b = PyImport_AddModule(__Pyx_NAMESTR(__Pyx_BUILTIN_MODULE_NAME)); if (unlikely(!__pyx_b)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #if CYTHON_COMPILING_IN_PYPY
  Py_INCREF(__pyx_b);
  #endif
  if (__Pyx_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  if (unlikely(__Pyx_InitGlobals() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #if PY_MAJOR_VERSION < 3 && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
  if (__Pyx_init_sys_getdefaultencoding_params() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  if (__pyx_module_is_main_lts___TraderApi) {
    if (__Pyx_SetAttrString(__pyx_m, "__name__", __pyx_n_s_main) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  }
  #if PY_MAJOR_VERSION >= 3
  {
    PyObject *modules = PyImport_GetModuleDict(); if (unlikely(!modules)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    if (!PyDict_GetItemString(modules, "lts._TraderApi")) {
      if (unlikely(PyDict_SetItemString(modules, "lts._TraderApi", __pyx_m) < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
  }
  #endif
  if (unlikely(__Pyx_InitCachedBuiltins() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(__Pyx_InitCachedConstants() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_v_3lts_10_TraderApi_ApiStruct_addressof = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_BondInterest = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_DepthMarketData = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_Exchange = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_FundTransfer = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_InputFundTransfer = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_InputOrder = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_InputOrderAction = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_Instrument = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_InstrumentCommissionRate = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_Investor = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_InvestorPosition = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_MarketRationInfo = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_Order = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_OrderAction = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_RspInfo = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_RspUserLogin = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_Trade = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_TradingAccount = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_TradingAccountPasswordUpdate = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_TradingCode = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_UserLogout = Py_None; Py_INCREF(Py_None);
  __pyx_v_3lts_10_TraderApi_ApiStruct_UserPasswordUpdate = Py_None; Py_INCREF(Py_None);
  if (PyType_Ready(&__pyx_type_3lts_10_TraderApi_TraderApi) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 40; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_type_3lts_10_TraderApi_TraderApi.tp_print = 0;
  if (__Pyx_SetAttrString(__pyx_m, "TraderApi", (PyObject *)&__pyx_type_3lts_10_TraderApi_TraderApi) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 40; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_3lts_10_TraderApi_TraderApi = &__pyx_type_3lts_10_TraderApi_TraderApi;
  XFixSysModules();
  __pyx_t_1 = PyObject_GetAttrString(__pyx_m, S___name__); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 33; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyCFunction_NewEx((&_init_method), NULL, __pyx_t_1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 33; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_3 = PyObject_SetAttrString(__pyx_m, _init_method.ml_name, __pyx_t_2); if (unlikely(__pyx_t_3 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 33; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_test, __pyx_t_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  if (__pyx_m) {
    __Pyx_AddTraceback("init lts._TraderApi", __pyx_clineno, __pyx_lineno, __pyx_filename);
    Py_DECREF(__pyx_m); __pyx_m = 0;
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_ImportError, "init lts._TraderApi");
  }
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  #if PY_MAJOR_VERSION < 3
  return;
  #else
  return __pyx_m;
  #endif
}
#if CYTHON_REFNANNY
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname) {
    PyObject *m = NULL, *p = NULL;
    void *r = NULL;
    m = PyImport_ImportModule((char *)modname);
    if (!m) goto end;
    p = PyObject_GetAttrString(m, (char *)"RefNannyAPI");
    if (!p) goto end;
    r = PyLong_AsVoidPtr(p);
end:
    Py_XDECREF(p);
    Py_XDECREF(m);
    return (__Pyx_RefNannyAPIStruct *)r;
}
#endif 
static void __Pyx_RaiseDoubleKeywordsError(
    const char* func_name,
    PyObject* kw_name)
{
    PyErr_Format(PyExc_TypeError,
        #if PY_MAJOR_VERSION >= 3
        "%s() got multiple values for keyword argument '%U'", func_name, kw_name);
        #else
        "%s() got multiple values for keyword argument '%s'", func_name,
        PyString_AsString(kw_name));
        #endif
}
static int __Pyx_ParseOptionalKeywords(
    PyObject *kwds,
    PyObject **argnames[],
    PyObject *kwds2,
    PyObject *values[],
    Py_ssize_t num_pos_args,
    const char* function_name)
{
    PyObject *key = 0, *value = 0;
    Py_ssize_t pos = 0;
    PyObject*** name;
    PyObject*** first_kw_arg = argnames + num_pos_args;
    while (PyDict_Next(kwds, &pos, &key, &value)) {
        name = first_kw_arg;
        while (*name && (**name != key)) name++;
        if (*name) {
            values[name-argnames] = value;
            continue;
        }
        name = first_kw_arg;
        #if PY_MAJOR_VERSION < 3
        if (likely(PyString_CheckExact(key)) || likely(PyString_Check(key))) {
            while (*name) {
                if ((CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**name) == PyString_GET_SIZE(key))
                        && _PyString_Eq(**name, key)) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    if ((**argname == key) || (
                            (CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**argname) == PyString_GET_SIZE(key))
                             && _PyString_Eq(**argname, key))) {
                        goto arg_passed_twice;
                    }
                    argname++;
                }
            }
        } else
        #endif
        if (likely(PyUnicode_Check(key))) {
            while (*name) {
                int cmp = (**name == key) ? 0 :
                #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                    (PyUnicode_GET_SIZE(**name) != PyUnicode_GET_SIZE(key)) ? 1 :
                #endif
                    PyUnicode_Compare(**name, key);
                if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                if (cmp == 0) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    int cmp = (**argname == key) ? 0 :
                    #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                        (PyUnicode_GET_SIZE(**argname) != PyUnicode_GET_SIZE(key)) ? 1 :
                    #endif
                        PyUnicode_Compare(**argname, key);
                    if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                    if (cmp == 0) goto arg_passed_twice;
                    argname++;
                }
            }
        } else
            goto invalid_keyword_type;
        if (kwds2) {
            if (unlikely(PyDict_SetItem(kwds2, key, value))) goto bad;
        } else {
            goto invalid_keyword;
        }
    }
    return 0;
arg_passed_twice:
    __Pyx_RaiseDoubleKeywordsError(function_name, key);
    goto bad;
invalid_keyword_type:
    PyErr_Format(PyExc_TypeError,
        "%.200s() keywords must be strings", function_name);
    goto bad;
invalid_keyword:
    PyErr_Format(PyExc_TypeError,
    #if PY_MAJOR_VERSION < 3
        "%.200s() got an unexpected keyword argument '%.200s'",
        function_name, PyString_AsString(key));
    #else
        "%s() got an unexpected keyword argument '%U'",
        function_name, key);
    #endif
bad:
    return -1;
}
static void __Pyx_RaiseArgtupleInvalid(
    const char* func_name,
    int exact,
    Py_ssize_t num_min,
    Py_ssize_t num_max,
    Py_ssize_t num_found)
{
    Py_ssize_t num_expected;
    const char *more_or_less;
    if (num_found < num_min) {
        num_expected = num_min;
        more_or_less = "at least";
    } else {
        num_expected = num_max;
        more_or_less = "at most";
    }
    if (exact) {
        more_or_less = "exactly";
    }
    PyErr_Format(PyExc_TypeError,
                 "%.200s() takes %.8s %" CYTHON_FORMAT_SSIZE_T "d positional argument%.1s (%" CYTHON_FORMAT_SSIZE_T "d given)",
                 func_name, more_or_less, num_expected,
                 (num_expected == 1) ? "" : "s", num_found);
}
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    PyObject *result;
    ternaryfunc call = func->ob_type->tp_call;
    if (unlikely(!call))
        return PyObject_Call(func, arg, kw);
#if PY_VERSION_HEX >= 0x02060000
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
#endif
    result = (*call)(func, arg, kw);
#if PY_VERSION_HEX >= 0x02060000
    Py_LeaveRecursiveCall();
#endif
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif
#define __PYX_VERIFY_RETURN_INT(target_type, func_type, func) \
    { \
        func_type value = func(x); \
        if (sizeof(target_type) < sizeof(func_type)) { \
            if (unlikely(value != (func_type) (target_type) value)) { \
                func_type zero = 0; \
                PyErr_SetString(PyExc_OverflowError, \
                    (is_unsigned && unlikely(value < zero)) ? \
                    "can't convert negative value to " #target_type : \
                    "value too large to convert to " #target_type); \
                return (target_type) -1; \
            } \
        } \
        return (target_type) value; \
    }
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
  #include "longintrepr.h"
 #endif
#endif
static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *x) {
    const int neg_one = (int) -1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(int) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(int, long, PyInt_AS_LONG)
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to int");
                return (int) -1;
            }
            return (int) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(int)) {
                switch (Py_SIZE(x)) {
                    case 0: return 0;
                    case 1: return (int) ((PyLongObject*)x)->ob_digit[0];
                }
            }
 #endif
#endif
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to int");
                return (int) -1;
            }
            if (sizeof(int) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT(int, unsigned long, PyLong_AsUnsignedLong)
            } else if (sizeof(int) <= sizeof(unsigned long long)) {
                __PYX_VERIFY_RETURN_INT(int, unsigned long long, PyLong_AsUnsignedLongLong)
            }
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(int)) {
                switch (Py_SIZE(x)) {
                    case 0: return 0;
                    case 1: return +(int) ((PyLongObject*)x)->ob_digit[0];
                    case -1: return -(int) ((PyLongObject*)x)->ob_digit[0];
                }
            }
 #endif
#endif
            if (sizeof(int) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT(int, long, PyLong_AsLong)
            } else if (sizeof(int) <= sizeof(long long)) {
                __PYX_VERIFY_RETURN_INT(int, long long, PyLong_AsLongLong)
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            int val;
            PyObject *v = __Pyx_PyNumber_Int(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (int) -1;
        }
    } else {
        int val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (int) -1;
        val = __Pyx_PyInt_As_int(tmp);
        Py_DECREF(tmp);
        return val;
    }
}
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value) {
    const long neg_one = (long) -1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(long) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
        } else if (sizeof(long) <= sizeof(unsigned long long)) {
            return PyLong_FromUnsignedLongLong((unsigned long long) value);
        }
    } else {
        if (sizeof(long) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(long long)) {
            return PyLong_FromLongLong((long long) value);
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(long),
                                     little, !is_unsigned);
    }
}
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_int(int value) {
    const int neg_one = (int) -1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(int) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(int) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
        } else if (sizeof(int) <= sizeof(unsigned long long)) {
            return PyLong_FromUnsignedLongLong((unsigned long long) value);
        }
    } else {
        if (sizeof(int) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(int) <= sizeof(long long)) {
            return PyLong_FromLongLong((long long) value);
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(int),
                                     little, !is_unsigned);
    }
}
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
  #include "longintrepr.h"
 #endif
#endif
static CYTHON_INLINE size_t __Pyx_PyInt_As_size_t(PyObject *x) {
    const size_t neg_one = (size_t) -1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(size_t) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(size_t, long, PyInt_AS_LONG)
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to size_t");
                return (size_t) -1;
            }
            return (size_t) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(size_t)) {
                switch (Py_SIZE(x)) {
                    case 0: return 0;
                    case 1: return (size_t) ((PyLongObject*)x)->ob_digit[0];
                }
            }
 #endif
#endif
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to size_t");
                return (size_t) -1;
            }
            if (sizeof(size_t) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT(size_t, unsigned long, PyLong_AsUnsignedLong)
            } else if (sizeof(size_t) <= sizeof(unsigned long long)) {
                __PYX_VERIFY_RETURN_INT(size_t, unsigned long long, PyLong_AsUnsignedLongLong)
            }
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(size_t)) {
                switch (Py_SIZE(x)) {
                    case 0: return 0;
                    case 1: return +(size_t) ((PyLongObject*)x)->ob_digit[0];
                    case -1: return -(size_t) ((PyLongObject*)x)->ob_digit[0];
                }
            }
 #endif
#endif
            if (sizeof(size_t) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT(size_t, long, PyLong_AsLong)
            } else if (sizeof(size_t) <= sizeof(long long)) {
                __PYX_VERIFY_RETURN_INT(size_t, long long, PyLong_AsLongLong)
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            size_t val;
            PyObject *v = __Pyx_PyNumber_Int(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (size_t) -1;
        }
    } else {
        size_t val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (size_t) -1;
        val = __Pyx_PyInt_As_size_t(tmp);
        Py_DECREF(tmp);
        return val;
    }
}
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
  #include "longintrepr.h"
 #endif
#endif
static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *x) {
    const long neg_one = (long) -1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(long) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(long, long, PyInt_AS_LONG)
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to long");
                return (long) -1;
            }
            return (long) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(long)) {
                switch (Py_SIZE(x)) {
                    case 0: return 0;
                    case 1: return (long) ((PyLongObject*)x)->ob_digit[0];
                }
            }
 #endif
#endif
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to long");
                return (long) -1;
            }
            if (sizeof(long) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT(long, unsigned long, PyLong_AsUnsignedLong)
            } else if (sizeof(long) <= sizeof(unsigned long long)) {
                __PYX_VERIFY_RETURN_INT(long, unsigned long long, PyLong_AsUnsignedLongLong)
            }
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(long)) {
                switch (Py_SIZE(x)) {
                    case 0: return 0;
                    case 1: return +(long) ((PyLongObject*)x)->ob_digit[0];
                    case -1: return -(long) ((PyLongObject*)x)->ob_digit[0];
                }
            }
 #endif
#endif
            if (sizeof(long) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT(long, long, PyLong_AsLong)
            } else if (sizeof(long) <= sizeof(long long)) {
                __PYX_VERIFY_RETURN_INT(long, long long, PyLong_AsLongLong)
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            long val;
            PyObject *v = __Pyx_PyNumber_Int(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (long) -1;
        }
    } else {
        long val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (long) -1;
        val = __Pyx_PyInt_As_long(tmp);
        Py_DECREF(tmp);
        return val;
    }
}
static int __Pyx_check_binary_version(void) {
    char ctversion[4], rtversion[4];
    PyOS_snprintf(ctversion, 4, "%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    PyOS_snprintf(rtversion, 4, "%s", Py_GetVersion());
    if (ctversion[0] != rtversion[0] || ctversion[2] != rtversion[2]) {
        char message[200];
        PyOS_snprintf(message, sizeof(message),
                      "compiletime version %s of module '%.100s' "
                      "does not match runtime version %s",
                      ctversion, __Pyx_MODULE_NAME, rtversion);
        #if PY_VERSION_HEX < 0x02050000
        return PyErr_Warn(NULL, message);
        #else
        return PyErr_WarnEx(NULL, message, 1);
        #endif
    }
    return 0;
}
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line) {
    int start = 0, mid = 0, end = count - 1;
    if (end >= 0 && code_line > entries[end].code_line) {
        return count;
    }
    while (start < end) {
        mid = (start + end) / 2;
        if (code_line < entries[mid].code_line) {
            end = mid;
        } else if (code_line > entries[mid].code_line) {
             start = mid + 1;
        } else {
            return mid;
        }
    }
    if (code_line <= entries[mid].code_line) {
        return mid;
    } else {
        return mid + 1;
    }
}
static PyCodeObject *__pyx_find_code_object(int code_line) {
    PyCodeObject* code_object;
    int pos;
    if (unlikely(!code_line) || unlikely(!__pyx_code_cache.entries)) {
        return NULL;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if (unlikely(pos >= __pyx_code_cache.count) || unlikely(__pyx_code_cache.entries[pos].code_line != code_line)) {
        return NULL;
    }
    code_object = __pyx_code_cache.entries[pos].code_object;
    Py_INCREF(code_object);
    return code_object;
}
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object) {
    int pos, i;
    __Pyx_CodeObjectCacheEntry* entries = __pyx_code_cache.entries;
    if (unlikely(!code_line)) {
        return;
    }
    if (unlikely(!entries)) {
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Malloc(64*sizeof(__Pyx_CodeObjectCacheEntry));
        if (likely(entries)) {
            __pyx_code_cache.entries = entries;
            __pyx_code_cache.max_count = 64;
            __pyx_code_cache.count = 1;
            entries[0].code_line = code_line;
            entries[0].code_object = code_object;
            Py_INCREF(code_object);
        }
        return;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if ((pos < __pyx_code_cache.count) && unlikely(__pyx_code_cache.entries[pos].code_line == code_line)) {
        PyCodeObject* tmp = entries[pos].code_object;
        entries[pos].code_object = code_object;
        Py_DECREF(tmp);
        return;
    }
    if (__pyx_code_cache.count == __pyx_code_cache.max_count) {
        int new_max = __pyx_code_cache.max_count + 64;
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Realloc(
            __pyx_code_cache.entries, (size_t)new_max*sizeof(__Pyx_CodeObjectCacheEntry));
        if (unlikely(!entries)) {
            return;
        }
        __pyx_code_cache.entries = entries;
        __pyx_code_cache.max_count = new_max;
    }
    for (i=__pyx_code_cache.count; i>pos; i--) {
        entries[i] = entries[i-1];
    }
    entries[pos].code_line = code_line;
    entries[pos].code_object = code_object;
    __pyx_code_cache.count++;
    Py_INCREF(code_object);
}
#include "compile.h"
#include "frameobject.h"
#include "traceback.h"
static PyCodeObject* __Pyx_CreateCodeObjectForTraceback(
            const char *funcname, int c_line,
            int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    #if PY_MAJOR_VERSION < 3
    py_srcfile = PyString_FromString(filename);
    #else
    py_srcfile = PyUnicode_FromString(filename);
    #endif
    if (!py_srcfile) goto bad;
    if (c_line) {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #else
        py_funcname = PyUnicode_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #endif
    }
    else {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromString(funcname);
        #else
        py_funcname = PyUnicode_FromString(funcname);
        #endif
    }
    if (!py_funcname) goto bad;
    py_code = __Pyx_PyCode_New(
        0, 
        0, 
        0, 
        0, 
        0, 
        __pyx_empty_bytes, 
        __pyx_empty_tuple, 
        __pyx_empty_tuple, 
        __pyx_empty_tuple, 
        __pyx_empty_tuple, 
        __pyx_empty_tuple, 
        py_srcfile, 
        py_funcname, 
        py_line, 
        __pyx_empty_bytes 
    );
    Py_DECREF(py_srcfile);
    Py_DECREF(py_funcname);
    return py_code;
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    return NULL;
}
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_globals = 0;
    PyFrameObject *py_frame = 0;
    py_code = __pyx_find_code_object(c_line ? c_line : py_line);
    if (!py_code) {
        py_code = __Pyx_CreateCodeObjectForTraceback(
            funcname, c_line, py_line, filename);
        if (!py_code) goto bad;
        __pyx_insert_code_object(c_line ? c_line : py_line, py_code);
    }
    py_globals = PyModule_GetDict(__pyx_m);
    if (!py_globals) goto bad;
    py_frame = PyFrame_New(
        PyThreadState_GET(), 
        py_code, 
        py_globals, 
        0 
    );
    if (!py_frame) goto bad;
    py_frame->f_lineno = py_line;
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}
static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        #if PY_MAJOR_VERSION < 3
        if (t->is_unicode) {
            *t->p = PyUnicode_DecodeUTF8(t->s, t->n - 1, NULL);
        } else if (t->intern) {
            *t->p = PyString_InternFromString(t->s);
        } else {
            *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        }
        #else 
        if (t->is_unicode | t->is_str) {
            if (t->intern) {
                *t->p = PyUnicode_InternFromString(t->s);
            } else if (t->encoding) {
                *t->p = PyUnicode_Decode(t->s, t->n - 1, t->encoding, NULL);
            } else {
                *t->p = PyUnicode_FromStringAndSize(t->s, t->n - 1);
            }
        } else {
            *t->p = PyBytes_FromStringAndSize(t->s, t->n - 1);
        }
        #endif
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char* c_str) {
    return __Pyx_PyUnicode_FromStringAndSize(c_str, (Py_ssize_t)strlen(c_str));
}
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject* o) {
    Py_ssize_t ignore;
    return __Pyx_PyObject_AsStringAndSize(o, &ignore);
}
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
    if (
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
            __Pyx_sys_getdefaultencoding_not_ascii &&
#endif
            PyUnicode_Check(o)) {
#if PY_VERSION_HEX < 0x03030000
        char* defenc_c;
        PyObject* defenc = _PyUnicode_AsDefaultEncodedString(o, NULL);
        if (!defenc) return NULL;
        defenc_c = PyBytes_AS_STRING(defenc);
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        {
            char* end = defenc_c + PyBytes_GET_SIZE(defenc);
            char* c;
            for (c = defenc_c; c < end; c++) {
                if ((unsigned char) (*c) >= 128) {
                    PyUnicode_AsASCIIString(o);
                    return NULL;
                }
            }
        }
#endif 
        *length = PyBytes_GET_SIZE(defenc);
        return defenc_c;
#else 
        if (PyUnicode_READY(o) == -1) return NULL;
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        if (PyUnicode_IS_ASCII(o)) {
            *length = PyUnicode_GET_LENGTH(o);
            return PyUnicode_AsUTF8(o);
        } else {
            PyUnicode_AsASCIIString(o);
            return NULL;
        }
#else 
        return PyUnicode_AsUTF8AndSize(o, length);
#endif 
#endif 
    } else
#endif 
#if !CYTHON_COMPILING_IN_PYPY
#if PY_VERSION_HEX >= 0x02060000
    if (PyByteArray_Check(o)) {
        *length = PyByteArray_GET_SIZE(o);
        return PyByteArray_AS_STRING(o);
    } else
#endif
#endif
    {
        char* result;
        int r = PyBytes_AsStringAndSize(o, &result, length);
        if (unlikely(r < 0)) {
            return NULL;
        } else {
            return result;
        }
    }
}
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject* x) {
   int is_true = x == Py_True;
   if (is_true | (x == Py_False) | (x == Py_None)) return is_true;
   else return PyObject_IsTrue(x);
}
static CYTHON_INLINE PyObject* __Pyx_PyNumber_Int(PyObject* x) {
  PyNumberMethods *m;
  const char *name = NULL;
  PyObject *res = NULL;
#if PY_MAJOR_VERSION < 3
  if (PyInt_Check(x) || PyLong_Check(x))
#else
  if (PyLong_Check(x))
#endif
    return Py_INCREF(x), x;
  m = Py_TYPE(x)->tp_as_number;
#if PY_MAJOR_VERSION < 3
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Int(x);
  }
  else if (m && m->nb_long) {
    name = "long";
    res = PyNumber_Long(x);
  }
#else
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Long(x);
  }
#endif
  if (res) {
#if PY_MAJOR_VERSION < 3
    if (!PyInt_Check(res) && !PyLong_Check(res)) {
#else
    if (!PyLong_Check(res)) {
#endif
      PyErr_Format(PyExc_TypeError,
                   "__%.4s__ returned non-%.4s (type %.200s)",
                   name, name, Py_TYPE(res)->tp_name);
      Py_DECREF(res);
      return NULL;
    }
  }
  else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_TypeError,
                    "an integer is required");
  }
  return res;
}
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
  #include "longintrepr.h"
 #endif
#endif
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject* b) {
  Py_ssize_t ival;
  PyObject *x;
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_CheckExact(b)))
      return PyInt_AS_LONG(b);
#endif
  if (likely(PyLong_CheckExact(b))) {
    #if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
     #if CYTHON_USE_PYLONG_INTERNALS
       switch (Py_SIZE(b)) {
       case -1: return -(sdigit)((PyLongObject*)b)->ob_digit[0];
       case 0: return 0;
       case 1: return ((PyLongObject*)b)->ob_digit[0];
       }
     #endif
    #endif
  #if PY_VERSION_HEX < 0x02060000
    return PyInt_AsSsize_t(b);
  #else
    return PyLong_AsSsize_t(b);
  #endif
  }
  x = PyNumber_Index(b);
  if (!x) return -1;
  ival = PyInt_AsSsize_t(x);
  Py_DECREF(x);
  return ival;
}
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t ival) {
#if PY_VERSION_HEX < 0x02050000
   if (ival <= LONG_MAX)
       return PyInt_FromLong((long)ival);
   else {
       unsigned char *bytes = (unsigned char *) &ival;
       int one = 1; int little = (int)*(unsigned char*)&one;
       return _PyLong_FromByteArray(bytes, sizeof(size_t), little, 0);
   }
#else
   return PyInt_FromSize_t(ival);
#endif
}
#endif 
