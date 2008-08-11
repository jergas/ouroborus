/* 0.9.7 on Sun Aug 10 16:27:28 2008 */

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

static int __Pyx_InternStrings(__Pyx_InternTabEntry *t); /*proto*/

static void __Pyx_AddTraceback(char *funcname); /*proto*/

/* Declarations from wanderer */



/* Implementation of wanderer */


static PyObject *__pyx_n_topology;
static PyObject *__pyx_n_neighborhood;
static PyObject *__pyx_n_rule;
static PyObject *__pyx_n_operator;
static PyObject *__pyx_n_automaton;
static PyObject *__pyx_n_agent;
static PyObject *__pyx_n_genome;
static PyObject *__pyx_n_random;

static PyObject *__pyx_n_VonNeumannNeighborhood;
static PyObject *__pyx_n_Agent_2D;
static PyObject *__pyx_n_Genome;

static PyObject *__pyx_f_8wanderer_beBorn(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_f_8wanderer_beBorn(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_topos = 0;
  PyObject *__pyx_v_ball;
  PyObject *__pyx_v_myself;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  PyObject *__pyx_6 = 0;
  PyObject *__pyx_7 = 0;
  static char *__pyx_argnames[] = {"topos",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_topos)) return 0;
  Py_INCREF(__pyx_v_topos);
  __pyx_v_ball = Py_None; Py_INCREF(Py_None);
  __pyx_v_myself = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":3 */
  __pyx_1 = __Pyx_GetName(__pyx_m, __pyx_n_neighborhood); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; goto __pyx_L1;}
  __pyx_2 = PyObject_GetAttr(__pyx_1, __pyx_n_VonNeumannNeighborhood); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  __pyx_1 = PyTuple_New(1); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; goto __pyx_L1;}
  Py_INCREF(__pyx_v_topos);
  PyTuple_SET_ITEM(__pyx_1, 0, __pyx_v_topos);
  __pyx_3 = PyObject_CallObject(__pyx_2, __pyx_1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_v_ball);
  __pyx_v_ball = __pyx_3;
  __pyx_3 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":4 */
  __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_agent); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  __pyx_1 = PyObject_GetAttr(__pyx_2, __pyx_n_Agent_2D); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_genome); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  __pyx_2 = PyObject_GetAttr(__pyx_3, __pyx_n_Genome); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  __pyx_3 = PyList_New(0); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  __pyx_4 = PyDict_New(); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  __pyx_5 = PyInt_FromLong(2); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  __pyx_6 = PyTuple_New(3); if (!__pyx_6) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_6, 0, __pyx_3);
  PyTuple_SET_ITEM(__pyx_6, 1, __pyx_4);
  PyTuple_SET_ITEM(__pyx_6, 2, __pyx_5);
  __pyx_3 = 0;
  __pyx_4 = 0;
  __pyx_5 = 0;
  __pyx_3 = PyObject_CallObject(__pyx_2, __pyx_6); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_6); __pyx_6 = 0;
  __pyx_4 = PyInt_FromLong(50); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  __pyx_5 = PyInt_FromLong(1); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong(30); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  __pyx_6 = PyInt_FromLong(8); if (!__pyx_6) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  __pyx_7 = PyTuple_New(2); if (!__pyx_7) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_7, 0, __pyx_2);
  PyTuple_SET_ITEM(__pyx_7, 1, __pyx_6);
  __pyx_2 = 0;
  __pyx_6 = 0;
  __pyx_2 = PyTuple_New(6); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_2, 0, __pyx_3);
  Py_INCREF(__pyx_v_ball);
  PyTuple_SET_ITEM(__pyx_2, 1, __pyx_v_ball);
  Py_INCREF(__pyx_v_ball);
  PyTuple_SET_ITEM(__pyx_2, 2, __pyx_v_ball);
  PyTuple_SET_ITEM(__pyx_2, 3, __pyx_4);
  PyTuple_SET_ITEM(__pyx_2, 4, __pyx_5);
  PyTuple_SET_ITEM(__pyx_2, 5, __pyx_7);
  __pyx_3 = 0;
  __pyx_4 = 0;
  __pyx_5 = 0;
  __pyx_7 = 0;
  __pyx_6 = PyObject_CallObject(__pyx_1, __pyx_2); if (!__pyx_6) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 4; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_v_myself);
  __pyx_v_myself = __pyx_6;
  __pyx_6 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":5 */
  Py_INCREF(__pyx_v_myself);
  __pyx_r = __pyx_v_myself;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  Py_XDECREF(__pyx_6);
  Py_XDECREF(__pyx_7);
  __Pyx_AddTraceback("wanderer.beBorn");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_ball);
  Py_DECREF(__pyx_v_myself);
  Py_DECREF(__pyx_v_topos);
  return __pyx_r;
}

static PyObject *__pyx_n_randint;
static PyObject *__pyx_n_changeFacing;
static PyObject *__pyx_n_advance;
static PyObject *__pyx_n_eatMana;

static PyObject *__pyx_f_8wanderer_wander(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_f_8wanderer_wander(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_agent = 0;
  PyObject *__pyx_v_direction;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  static char *__pyx_argnames[] = {"agent",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_agent)) return 0;
  Py_INCREF(__pyx_v_agent);
  __pyx_v_direction = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":7 */
  __pyx_1 = __Pyx_GetName(__pyx_m, __pyx_n_random); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 7; goto __pyx_L1;}
  __pyx_2 = PyObject_GetAttr(__pyx_1, __pyx_n_randint); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 7; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  __pyx_1 = PyInt_FromLong(0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 7; goto __pyx_L1;}
  __pyx_3 = PyInt_FromLong(4); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 7; goto __pyx_L1;}
  __pyx_4 = PyTuple_New(2); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 7; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_4, 0, __pyx_1);
  PyTuple_SET_ITEM(__pyx_4, 1, __pyx_3);
  __pyx_1 = 0;
  __pyx_3 = 0;
  __pyx_1 = PyObject_CallObject(__pyx_2, __pyx_4); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 7; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_4); __pyx_4 = 0;
  Py_DECREF(__pyx_v_direction);
  __pyx_v_direction = __pyx_1;
  __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":8 */
  __pyx_3 = PyObject_GetAttr(__pyx_v_agent, __pyx_n_changeFacing); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 8; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(1); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 8; goto __pyx_L1;}
  Py_INCREF(__pyx_v_direction);
  PyTuple_SET_ITEM(__pyx_2, 0, __pyx_v_direction);
  __pyx_4 = PyObject_CallObject(__pyx_3, __pyx_2); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 8; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_4); __pyx_4 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":9 */
  __pyx_1 = PyObject_GetAttr(__pyx_v_agent, __pyx_n_advance); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 9; goto __pyx_L1;}
  __pyx_3 = PyObject_CallObject(__pyx_1, 0); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 9; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":10 */
  __pyx_2 = PyObject_GetAttr(__pyx_v_agent, __pyx_n_eatMana); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 10; goto __pyx_L1;}
  __pyx_4 = PyObject_CallObject(__pyx_2, 0); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 10; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_4); __pyx_4 = 0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  __Pyx_AddTraceback("wanderer.wander");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_direction);
  Py_DECREF(__pyx_v_agent);
  return __pyx_r;
}

static __Pyx_InternTabEntry __pyx_intern_tab[] = {
  {&__pyx_n_Agent_2D, "Agent_2D"},
  {&__pyx_n_Genome, "Genome"},
  {&__pyx_n_VonNeumannNeighborhood, "VonNeumannNeighborhood"},
  {&__pyx_n_advance, "advance"},
  {&__pyx_n_agent, "agent"},
  {&__pyx_n_automaton, "automaton"},
  {&__pyx_n_changeFacing, "changeFacing"},
  {&__pyx_n_eatMana, "eatMana"},
  {&__pyx_n_genome, "genome"},
  {&__pyx_n_neighborhood, "neighborhood"},
  {&__pyx_n_operator, "operator"},
  {&__pyx_n_randint, "randint"},
  {&__pyx_n_random, "random"},
  {&__pyx_n_rule, "rule"},
  {&__pyx_n_topology, "topology"},
  {0, 0}
};

static struct PyMethodDef __pyx_methods[] = {
  {"beBorn", (PyCFunction)__pyx_f_8wanderer_beBorn, METH_VARARGS|METH_KEYWORDS, 0},
  {"wander", (PyCFunction)__pyx_f_8wanderer_wander, METH_VARARGS|METH_KEYWORDS, 0},
  {0, 0, 0, 0}
};

static void __pyx_init_filenames(void); /*proto*/

PyMODINIT_FUNC initwanderer(void); /*proto*/
PyMODINIT_FUNC initwanderer(void) {
  PyObject *__pyx_1 = 0;
  __pyx_init_filenames();
  __pyx_m = Py_InitModule4("wanderer", __pyx_methods, 0, 0, PYTHON_API_VERSION);
  if (!__pyx_m) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;};
  Py_INCREF(__pyx_m);
  __pyx_b = PyImport_AddModule("__builtin__");
  if (!__pyx_b) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;};
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;};
  if (__Pyx_InternStrings(__pyx_intern_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;};

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":1 */
  __pyx_1 = __Pyx_Import(__pyx_n_topology, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_topology, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":1 */
  __pyx_1 = __Pyx_Import(__pyx_n_neighborhood, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_neighborhood, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":1 */
  __pyx_1 = __Pyx_Import(__pyx_n_rule, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_rule, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":1 */
  __pyx_1 = __Pyx_Import(__pyx_n_operator, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_operator, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":1 */
  __pyx_1 = __Pyx_Import(__pyx_n_automaton, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_automaton, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":1 */
  __pyx_1 = __Pyx_Import(__pyx_n_agent, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_agent, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":1 */
  __pyx_1 = __Pyx_Import(__pyx_n_genome, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_genome, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":1 */
  __pyx_1 = __Pyx_Import(__pyx_n_random, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_random, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/creatures/wanderer.pyx":6 */
  return;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("wanderer");
}

static char *__pyx_filenames[] = {
  "wanderer.pyx",
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

static int __Pyx_InternStrings(__Pyx_InternTabEntry *t) {
    while (t->p) {
        *t->p = PyString_InternFromString(t->s);
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
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
