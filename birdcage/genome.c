/* 0.9.7.2 on Thu Sep 25 19:21:14 2008 */

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "structmember.h"
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#if PY_VERSION_HEX < 0x02050000
  typedef int Py_ssize_t;
  #define PY_SSIZE_T_MAX INT_MAX
  #define PY_SSIZE_T_MIN INT_MIN
  #define PyInt_FromSsize_t(z) PyInt_FromLong(z)
  #define PyInt_AsSsize_t(o)	PyInt_AsLong(o)
#endif
#ifndef WIN32
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
#endif
#ifdef __cplusplus
#define __PYX_EXTERN_C extern "C"
#else
#define __PYX_EXTERN_C extern
#endif
#include <math.h>


typedef struct {PyObject **p; char *s;} __Pyx_InternTabEntry; /*proto*/
typedef struct {PyObject **p; char *s; long n;} __Pyx_StringTabEntry; /*proto*/

static PyObject *__pyx_m;
static PyObject *__pyx_b;
static int __pyx_lineno;
static char *__pyx_filename;
static char **__pyx_f;

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list); /*proto*/

static PyObject *__Pyx_GetName(PyObject *dict, PyObject *name); /*proto*/

static PyObject *__Pyx_GetItemInt(PyObject *o, Py_ssize_t i); /*proto*/

static int __Pyx_InternStrings(__Pyx_InternTabEntry *t); /*proto*/

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t); /*proto*/

static int __Pyx_SetVtable(PyObject *dict, void *vtable); /*proto*/

static void __Pyx_AddTraceback(char *funcname); /*proto*/

/* Declarations from genome */

struct __pyx_obj_6genome_Genome {
  PyObject_HEAD
  struct __pyx_vtabstruct_6genome_Genome *__pyx_vtab;
  PyObject *text;
  PyObject *table;
  int wordlength;
};


struct __pyx_vtabstruct_6genome_Genome {
  PyObject *(*pyx_readWord)(struct __pyx_obj_6genome_Genome *,int);
  PyObject *(*pyx_decode)(struct __pyx_obj_6genome_Genome *,PyObject *);
  PyObject *(*pyx_parse)(struct __pyx_obj_6genome_Genome *);
};
static struct __pyx_vtabstruct_6genome_Genome *__pyx_vtabptr_6genome_Genome;

static PyTypeObject *__pyx_ptype_6genome_Genome = 0;


/* Implementation of genome */


static PyObject *__pyx_n_exceptions_birdcage;
static PyObject *__pyx_n_E;

static int __pyx_f_6genome_6Genome___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_6genome_6Genome___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_text = 0;
  PyObject *__pyx_v_table = 0;
  int __pyx_v_wordlength;
  int __pyx_r;
  static char *__pyx_argnames[] = {"text","table","wordlength",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "OOi", __pyx_argnames, &__pyx_v_text, &__pyx_v_table, &__pyx_v_wordlength)) return -1;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_text);
  Py_INCREF(__pyx_v_table);

  /* "/home/panx/ouroborus/birdcage/genome.pyx":40 */
  Py_INCREF(__pyx_v_text);
  Py_DECREF(((struct __pyx_obj_6genome_Genome *)__pyx_v_self)->text);
  ((struct __pyx_obj_6genome_Genome *)__pyx_v_self)->text = __pyx_v_text;

  /* "/home/panx/ouroborus/birdcage/genome.pyx":41 */
  Py_INCREF(__pyx_v_table);
  Py_DECREF(((struct __pyx_obj_6genome_Genome *)__pyx_v_self)->table);
  ((struct __pyx_obj_6genome_Genome *)__pyx_v_self)->table = __pyx_v_table;

  /* "/home/panx/ouroborus/birdcage/genome.pyx":42 */
  ((struct __pyx_obj_6genome_Genome *)__pyx_v_self)->wordlength = __pyx_v_wordlength;

  __pyx_r = 0;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_text);
  Py_DECREF(__pyx_v_table);
  return __pyx_r;
}

static PyObject *__pyx_n_range;

static PyObject *__pyx_k2p;

static char __pyx_k2[] = "";

static PyObject *__pyx_f_6genome_6Genome_pyx_readWord(struct __pyx_obj_6genome_Genome *__pyx_v_self,int __pyx_v_index) {
  int __pyx_v_i;
  PyObject *__pyx_v_word;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  int __pyx_4;
  Py_INCREF(__pyx_v_self);
  __pyx_v_word = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/genome.pyx":53 */
  Py_INCREF(__pyx_k2p);
  Py_DECREF(__pyx_v_word);
  __pyx_v_word = __pyx_k2p;

  /* "/home/panx/ouroborus/birdcage/genome.pyx":55 */
  __pyx_1 = __Pyx_GetName(__pyx_b, __pyx_n_range); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 55; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong(__pyx_v_self->wordlength); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 55; goto __pyx_L1;}
  __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 55; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_3, 0, __pyx_2);
  __pyx_2 = 0;
  __pyx_2 = PyObject_CallObject(__pyx_1, __pyx_3); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 55; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  __pyx_1 = PyObject_GetIter(__pyx_2); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 55; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  for (;;) {
    __pyx_3 = PyIter_Next(__pyx_1);
    if (!__pyx_3) {
      if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 55; goto __pyx_L1;}
      break;
    }
    __pyx_4 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 55; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_v_i = __pyx_4;
    __pyx_2 = __Pyx_GetItemInt(__pyx_v_self->text, (__pyx_v_index + __pyx_v_i)); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; goto __pyx_L1;}
    __pyx_3 = PyNumber_Add(__pyx_v_word, __pyx_2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_v_word);
    __pyx_v_word = __pyx_3;
    __pyx_3 = 0;
  }
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/genome.pyx":58 */
  Py_INCREF(__pyx_v_word);
  __pyx_r = __pyx_v_word;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("genome.Genome.pyx_readWord");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_word);
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_6genome_6Genome_pyx_decode(struct __pyx_obj_6genome_Genome *__pyx_v_self,PyObject *__pyx_v_word) {
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_word);
  __pyx_1 = PyObject_GetItem(__pyx_v_self->table, __pyx_v_word); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 67; goto __pyx_L1;}
  __pyx_r = __pyx_1;
  __pyx_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("genome.Genome.pyx_decode");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_word);
  return __pyx_r;
}

static PyObject *__pyx_f_6genome_6Genome_parse(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_6genome_6Genome_parse[] = "Translate the entire text of the genome, word for word\n\n          return -->> a Python string, a sequence of Python instructions";
static PyObject *__pyx_f_6genome_6Genome_parse(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF(__pyx_v_self);
  __pyx_1 = ((struct __pyx_vtabstruct_6genome_Genome *)((struct __pyx_obj_6genome_Genome *)__pyx_v_self)->__pyx_vtab)->pyx_parse(((struct __pyx_obj_6genome_Genome *)__pyx_v_self)); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 75; goto __pyx_L1;}
  __pyx_r = __pyx_1;
  __pyx_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("genome.Genome.parse");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_k3p;
static PyObject *__pyx_k4p;

static char __pyx_k3[] = "";
static char __pyx_k4[] = "\n";

static PyObject *__pyx_f_6genome_6Genome_pyx_parse(struct __pyx_obj_6genome_Genome *__pyx_v_self) {
  int __pyx_v_i;
  PyObject *__pyx_v_code;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  Py_ssize_t __pyx_3;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  PyObject *__pyx_6 = 0;
  int __pyx_7;
  Py_INCREF(__pyx_v_self);
  __pyx_v_code = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/genome.pyx":85 */
  Py_INCREF(__pyx_k3p);
  Py_DECREF(__pyx_v_code);
  __pyx_v_code = __pyx_k3p;

  /* "/home/panx/ouroborus/birdcage/genome.pyx":87 */
  __pyx_1 = __Pyx_GetName(__pyx_b, __pyx_n_range); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong(0); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; goto __pyx_L1;}
  __pyx_3 = PyObject_Length(__pyx_v_self->text); if (__pyx_3 == -1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; goto __pyx_L1;}
  __pyx_4 = PyInt_FromSsize_t(__pyx_3); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; goto __pyx_L1;}
  __pyx_5 = PyInt_FromLong(__pyx_v_self->wordlength); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; goto __pyx_L1;}
  __pyx_6 = PyTuple_New(3); if (!__pyx_6) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_6, 0, __pyx_2);
  PyTuple_SET_ITEM(__pyx_6, 1, __pyx_4);
  PyTuple_SET_ITEM(__pyx_6, 2, __pyx_5);
  __pyx_2 = 0;
  __pyx_4 = 0;
  __pyx_5 = 0;
  __pyx_2 = PyObject_CallObject(__pyx_1, __pyx_6); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_6); __pyx_6 = 0;
  __pyx_4 = PyObject_GetIter(__pyx_2); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  for (;;) {
    __pyx_5 = PyIter_Next(__pyx_4);
    if (!__pyx_5) {
      if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; goto __pyx_L1;}
      break;
    }
    __pyx_7 = PyInt_AsLong(__pyx_5); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; goto __pyx_L1;}
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    __pyx_v_i = __pyx_7;
    __pyx_1 = ((struct __pyx_vtabstruct_6genome_Genome *)__pyx_v_self->__pyx_vtab)->pyx_readWord(__pyx_v_self,__pyx_v_i); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; goto __pyx_L1;}
    __pyx_6 = ((struct __pyx_vtabstruct_6genome_Genome *)__pyx_v_self->__pyx_vtab)->pyx_decode(__pyx_v_self,__pyx_1); if (!__pyx_6) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; goto __pyx_L1;}
    Py_DECREF(__pyx_1); __pyx_1 = 0;
    __pyx_2 = PyNumber_Add(__pyx_v_code, __pyx_6); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; goto __pyx_L1;}
    Py_DECREF(__pyx_6); __pyx_6 = 0;
    __pyx_5 = PyNumber_Add(__pyx_2, __pyx_k4p); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_v_code);
    __pyx_v_code = __pyx_5;
    __pyx_5 = 0;
  }
  Py_DECREF(__pyx_4); __pyx_4 = 0;

  /* "/home/panx/ouroborus/birdcage/genome.pyx":90 */
  Py_INCREF(__pyx_v_code);
  __pyx_r = __pyx_v_code;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  Py_XDECREF(__pyx_6);
  __Pyx_AddTraceback("genome.Genome.pyx_parse");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_code);
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_n_w;
static PyObject *__pyx_n_parse;
static PyObject *__pyx_n_write;
static PyObject *__pyx_n_close;


static PyObject *__pyx_f_6genome_6Genome_incorporate(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_6genome_6Genome_incorporate[] = "Create a file (body) with the python code which is the parsed genome";
static PyObject *__pyx_f_6genome_6Genome_incorporate(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_name = 0;
  PyObject *__pyx_v_body;
  PyObject *__pyx_v_code;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  static char *__pyx_argnames[] = {"name",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_name)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_name);
  __pyx_v_body = Py_None; Py_INCREF(Py_None);
  __pyx_v_code = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/genome.pyx":96 */
  __pyx_1 = PyTuple_New(2); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 96; goto __pyx_L1;}
  Py_INCREF(__pyx_v_name);
  PyTuple_SET_ITEM(__pyx_1, 0, __pyx_v_name);
  Py_INCREF(__pyx_n_w);
  PyTuple_SET_ITEM(__pyx_1, 1, __pyx_n_w);
  __pyx_2 = PyObject_CallObject(((PyObject *)(&PyFile_Type)), __pyx_1); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 96; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_v_body);
  __pyx_v_body = __pyx_2;
  __pyx_2 = 0;

  /* "/home/panx/ouroborus/birdcage/genome.pyx":97 */
  __pyx_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_parse); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; goto __pyx_L1;}
  __pyx_2 = PyObject_CallObject(__pyx_1, 0); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_v_code);
  __pyx_v_code = __pyx_2;
  __pyx_2 = 0;

  /* "/home/panx/ouroborus/birdcage/genome.pyx":98 */
  __pyx_1 = PyObject_GetAttr(__pyx_v_body, __pyx_n_write); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(1); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; goto __pyx_L1;}
  Py_INCREF(__pyx_v_code);
  PyTuple_SET_ITEM(__pyx_2, 0, __pyx_v_code);
  __pyx_3 = PyObject_CallObject(__pyx_1, __pyx_2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;

  /* "/home/panx/ouroborus/birdcage/genome.pyx":99 */
  __pyx_1 = PyObject_GetAttr(__pyx_v_body, __pyx_n_close); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 99; goto __pyx_L1;}
  __pyx_2 = PyObject_CallObject(__pyx_1, 0); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 99; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("genome.Genome.incorporate");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_body);
  Py_DECREF(__pyx_v_code);
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_name);
  return __pyx_r;
}

static __Pyx_InternTabEntry __pyx_intern_tab[] = {
  {&__pyx_n_E, "E"},
  {&__pyx_n_close, "close"},
  {&__pyx_n_exceptions_birdcage, "exceptions_birdcage"},
  {&__pyx_n_parse, "parse"},
  {&__pyx_n_range, "range"},
  {&__pyx_n_w, "w"},
  {&__pyx_n_write, "write"},
  {0, 0}
};

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_k2p, __pyx_k2, sizeof(__pyx_k2)},
  {&__pyx_k3p, __pyx_k3, sizeof(__pyx_k3)},
  {&__pyx_k4p, __pyx_k4, sizeof(__pyx_k4)},
  {0, 0, 0}
};
static struct __pyx_vtabstruct_6genome_Genome __pyx_vtable_6genome_Genome;

static PyObject *__pyx_tp_new_6genome_Genome(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_6genome_Genome *p;
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  p = ((struct __pyx_obj_6genome_Genome *)o);
  *(struct __pyx_vtabstruct_6genome_Genome **)&p->__pyx_vtab = __pyx_vtabptr_6genome_Genome;
  p->text = Py_None; Py_INCREF(Py_None);
  p->table = Py_None; Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_6genome_Genome(PyObject *o) {
  struct __pyx_obj_6genome_Genome *p = (struct __pyx_obj_6genome_Genome *)o;
  Py_XDECREF(p->text);
  Py_XDECREF(p->table);
  (*o->ob_type->tp_free)(o);
}

static int __pyx_tp_traverse_6genome_Genome(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_6genome_Genome *p = (struct __pyx_obj_6genome_Genome *)o;
  if (p->text) {
    e = (*v)(p->text, a); if (e) return e;
  }
  if (p->table) {
    e = (*v)(p->table, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_6genome_Genome(PyObject *o) {
  struct __pyx_obj_6genome_Genome *p = (struct __pyx_obj_6genome_Genome *)o;
  PyObject *t;
  t = p->text; 
  p->text = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = p->table; 
  p->table = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  return 0;
}

static struct PyMethodDef __pyx_methods_6genome_Genome[] = {
  {"parse", (PyCFunction)__pyx_f_6genome_6Genome_parse, METH_VARARGS|METH_KEYWORDS, __pyx_doc_6genome_6Genome_parse},
  {"incorporate", (PyCFunction)__pyx_f_6genome_6Genome_incorporate, METH_VARARGS|METH_KEYWORDS, __pyx_doc_6genome_6Genome_incorporate},
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_Genome = {
  0, /*nb_add*/
  0, /*nb_subtract*/
  0, /*nb_multiply*/
  0, /*nb_divide*/
  0, /*nb_remainder*/
  0, /*nb_divmod*/
  0, /*nb_power*/
  0, /*nb_negative*/
  0, /*nb_positive*/
  0, /*nb_absolute*/
  0, /*nb_nonzero*/
  0, /*nb_invert*/
  0, /*nb_lshift*/
  0, /*nb_rshift*/
  0, /*nb_and*/
  0, /*nb_xor*/
  0, /*nb_or*/
  0, /*nb_coerce*/
  0, /*nb_int*/
  0, /*nb_long*/
  0, /*nb_float*/
  0, /*nb_oct*/
  0, /*nb_hex*/
  0, /*nb_inplace_add*/
  0, /*nb_inplace_subtract*/
  0, /*nb_inplace_multiply*/
  0, /*nb_inplace_divide*/
  0, /*nb_inplace_remainder*/
  0, /*nb_inplace_power*/
  0, /*nb_inplace_lshift*/
  0, /*nb_inplace_rshift*/
  0, /*nb_inplace_and*/
  0, /*nb_inplace_xor*/
  0, /*nb_inplace_or*/
  0, /*nb_floor_divide*/
  0, /*nb_true_divide*/
  0, /*nb_inplace_floor_divide*/
  0, /*nb_inplace_true_divide*/
  #if Py_TPFLAGS_DEFAULT & Py_TPFLAGS_HAVE_INDEX
  0, /*nb_index*/
  #endif
};

static PySequenceMethods __pyx_tp_as_sequence_Genome = {
  0, /*sq_length*/
  0, /*sq_concat*/
  0, /*sq_repeat*/
  0, /*sq_item*/
  0, /*sq_slice*/
  0, /*sq_ass_item*/
  0, /*sq_ass_slice*/
  0, /*sq_contains*/
  0, /*sq_inplace_concat*/
  0, /*sq_inplace_repeat*/
};

static PyMappingMethods __pyx_tp_as_mapping_Genome = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_Genome = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_6genome_Genome = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "genome.Genome", /*tp_name*/
  sizeof(struct __pyx_obj_6genome_Genome), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_6genome_Genome, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_Genome, /*tp_as_number*/
  &__pyx_tp_as_sequence_Genome, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_Genome, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_Genome, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  "Base class for the Genome of an Agent_2D", /*tp_doc*/
  __pyx_tp_traverse_6genome_Genome, /*tp_traverse*/
  __pyx_tp_clear_6genome_Genome, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_6genome_Genome, /*tp_methods*/
  0, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_f_6genome_6Genome___init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_6genome_Genome, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
};

static struct PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

static void __pyx_init_filenames(void); /*proto*/

PyMODINIT_FUNC initgenome(void); /*proto*/
PyMODINIT_FUNC initgenome(void) {
  PyObject *__pyx_1 = 0;
  __pyx_init_filenames();
  __pyx_m = Py_InitModule4("genome", __pyx_methods, 0, 0, PYTHON_API_VERSION);
  if (!__pyx_m) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; goto __pyx_L1;};
  Py_INCREF(__pyx_m);
  __pyx_b = PyImport_AddModule("__builtin__");
  if (!__pyx_b) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; goto __pyx_L1;};
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; goto __pyx_L1;};
  if (__Pyx_InternStrings(__pyx_intern_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; goto __pyx_L1;};
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; goto __pyx_L1;};
  __pyx_vtabptr_6genome_Genome = &__pyx_vtable_6genome_Genome;
  *(void(**)(void))&__pyx_vtable_6genome_Genome.pyx_readWord = (void(*)(void))__pyx_f_6genome_6Genome_pyx_readWord;
  *(void(**)(void))&__pyx_vtable_6genome_Genome.pyx_decode = (void(*)(void))__pyx_f_6genome_6Genome_pyx_decode;
  *(void(**)(void))&__pyx_vtable_6genome_Genome.pyx_parse = (void(*)(void))__pyx_f_6genome_6Genome_pyx_parse;
  __pyx_type_6genome_Genome.tp_free = _PyObject_GC_Del;
  if (PyType_Ready(&__pyx_type_6genome_Genome) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; goto __pyx_L1;}
  if (__Pyx_SetVtable(__pyx_type_6genome_Genome.tp_dict, __pyx_vtabptr_6genome_Genome) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "Genome", (PyObject *)&__pyx_type_6genome_Genome) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; goto __pyx_L1;}
  __pyx_ptype_6genome_Genome = &__pyx_type_6genome_Genome;

  /* "/home/panx/ouroborus/birdcage/genome.pyx":20 */
  __pyx_1 = __Pyx_Import(__pyx_n_exceptions_birdcage, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_E, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/genome.pyx":93 */
  return;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("genome");
}

static char *__pyx_filenames[] = {
  "genome.pyx",
};

/* Runtime support code */

static void __pyx_init_filenames(void) {
  __pyx_f = __pyx_filenames;
}

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list) {
    PyObject *__import__ = 0;
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    __import__ = PyObject_GetAttrString(__pyx_b, "__import__");
    if (!__import__)
        goto bad;
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    module = PyObject_CallFunction(__import__, "OOOO",
        name, global_dict, empty_dict, list);
bad:
    Py_XDECREF(empty_list);
    Py_XDECREF(__import__);
    Py_XDECREF(empty_dict);
    return module;
}

static PyObject *__Pyx_GetName(PyObject *dict, PyObject *name) {
    PyObject *result;
    result = PyObject_GetAttr(dict, name);
    if (!result)
        PyErr_SetObject(PyExc_NameError, name);
    return result;
}

static PyObject *__Pyx_GetItemInt(PyObject *o, Py_ssize_t i) {
    PyTypeObject *t = o->ob_type;
    PyObject *r;
    if (t->tp_as_sequence && t->tp_as_sequence->sq_item)
        r = PySequence_GetItem(o, i);
    else {
        PyObject *j = PyInt_FromLong(i);
        if (!j)
            return 0;
        r = PyObject_GetItem(o, j);
        Py_DECREF(j);
    }
    return r;
}

static int __Pyx_InternStrings(__Pyx_InternTabEntry *t) {
    while (t->p) {
        *t->p = PyString_InternFromString(t->s);
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

static int __Pyx_SetVtable(PyObject *dict, void *vtable) {
    PyObject *pycobj = 0;
    int result;
    
    pycobj = PyCObject_FromVoidPtr(vtable, 0);
    if (!pycobj)
        goto bad;
    if (PyDict_SetItemString(dict, "__pyx_vtable__", pycobj) < 0)
        goto bad;
    result = 0;
    goto done;

bad:
    result = -1;
done:
    Py_XDECREF(pycobj);
    return result;
}

#include "compile.h"
#include "frameobject.h"
#include "traceback.h"

static void __Pyx_AddTraceback(char *funcname) {
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    PyObject *py_globals = 0;
    PyObject *empty_tuple = 0;
    PyObject *empty_string = 0;
    PyCodeObject *py_code = 0;
    PyFrameObject *py_frame = 0;
    
    py_srcfile = PyString_FromString(__pyx_filename);
    if (!py_srcfile) goto bad;
    py_funcname = PyString_FromString(funcname);
    if (!py_funcname) goto bad;
    py_globals = PyModule_GetDict(__pyx_m);
    if (!py_globals) goto bad;
    empty_tuple = PyTuple_New(0);
    if (!empty_tuple) goto bad;
    empty_string = PyString_FromString("");
    if (!empty_string) goto bad;
    py_code = PyCode_New(
        0,            /*int argcount,*/
        0,            /*int nlocals,*/
        0,            /*int stacksize,*/
        0,            /*int flags,*/
        empty_string, /*PyObject *code,*/
        empty_tuple,  /*PyObject *consts,*/
        empty_tuple,  /*PyObject *names,*/
        empty_tuple,  /*PyObject *varnames,*/
        empty_tuple,  /*PyObject *freevars,*/
        empty_tuple,  /*PyObject *cellvars,*/
        py_srcfile,   /*PyObject *filename,*/
        py_funcname,  /*PyObject *name,*/
        __pyx_lineno,   /*int firstlineno,*/
        empty_string  /*PyObject *lnotab*/
    );
    if (!py_code) goto bad;
    py_frame = PyFrame_New(
        PyThreadState_Get(), /*PyThreadState *tstate,*/
        py_code,             /*PyCodeObject *code,*/
        py_globals,          /*PyObject *globals,*/
        0                    /*PyObject *locals*/
    );
    if (!py_frame) goto bad;
    py_frame->f_lineno = __pyx_lineno;
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    Py_XDECREF(empty_tuple);
    Py_XDECREF(empty_string);
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}
