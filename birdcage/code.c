/* 0.9.7.2 on Mon Sep 22 17:28:24 2008 */

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

static int __Pyx_InternStrings(__Pyx_InternTabEntry *t); /*proto*/

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t); /*proto*/

static void __Pyx_AddTraceback(char *funcname); /*proto*/

/* Declarations from code */



/* Implementation of code */

static char __pyx_k2[] = "import topology; import neighborhood; import agent";
static char __pyx_k4[] = "corporality = neighborhood.VonNeumannNeighborhood";
static char __pyx_k6[] = "sensoriality = neighborhood.VonNeumannNeighborhood";
static char __pyx_k8[] = "def birth(earth, code, prana, mana, address):";
static char __pyx_k10[] = "  myself = agent.Agent_2D(code,corporality(earth.returnTopology()),sensoriality(earth.returnTopology()),prana,mana,address)";
static char __pyx_k12[] = "  return myself";
static char __pyx_k14[] = "def live(agent):";
static char __pyx_k16[] = "  pass";
static char __pyx_k18[] = "import topolog; import neighborhood; import rule; import operator; import automaton; import agent; import genome; import random";
static char __pyx_k20[] = "topos = topology.ToroidTopology((90,40),0)";
static char __pyx_k22[] = "change = rule.ReductionRule(ball,(operator.xor,0))";
static char __pyx_k24[] = "robot = automaton.SynchronousAutomaton_2D(change)";
static char __pyx_k26[] = "class corpus:";
static char __pyx_k28[] = "  ";
static char __pyx_k30[] = "def __init__(self, topos):";
static char __pyx_k32[] = "  self.topos = topos";
static char __pyx_k34[] = "  self.ball = neighborhood.VonNeumannNeighborhood(topos)";
static char __pyx_k36[] = "def wander(agent):";
static char __pyx_k38[] = "  direction = random.randint(0,4)";
static char __pyx_k40[] = "  agent.changeFacing(direction)";
static char __pyx_k42[] = "  agent.advance()";
static char __pyx_k44[] = "  agent.eatMana()";
static char __pyx_k46[] = "def beBorn(topos):";
static char __pyx_k48[] = "  ball = neighborhood.VonNeumannNeighborhood(topos)";
static char __pyx_k50[] = "  myself = agent.Agent_2D(genome.Genome([],{},2),ball,ball,50,1,(30,8))";
static char __pyx_k52[] = "  return myself";
static char __pyx_k54[] = "def __print__():";
static char __pyx_k56[] = "  return myself.tellAddress()";

static PyObject *__pyx_n_Yi;
static PyObject *__pyx_n_Yc;
static PyObject *__pyx_n_Ys;
static PyObject *__pyx_n_Cb;
static PyObject *__pyx_n_Cd;
static PyObject *__pyx_n_Cr;
static PyObject *__pyx_n_Tf;
static PyObject *__pyx_n_Tp;
static PyObject *__pyx_n_tabula;
static PyObject *__pyx_n_ai;
static PyObject *__pyx_n_at;
static PyObject *__pyx_n_ap;
static PyObject *__pyx_n_au;
static PyObject *__pyx_n_ic;
static PyObject *__pyx_n_ii;
static PyObject *__pyx_n_id;
static PyObject *__pyx_n_it;
static PyObject *__pyx_n_an;
static PyObject *__pyx_n_aw;
static PyObject *__pyx_n_ar;
static PyObject *__pyx_n_ac;
static PyObject *__pyx_n_aa;
static PyObject *__pyx_n_ae;
static PyObject *__pyx_n_zd;
static PyObject *__pyx_n_zn;
static PyObject *__pyx_n_zm;
static PyObject *__pyx_n_za;
static PyObject *__pyx_n_pd;
static PyObject *__pyx_n_pp;
static PyObject *__pyx_n_tabula_antica;

static PyObject *__pyx_k2p;
static PyObject *__pyx_k4p;
static PyObject *__pyx_k6p;
static PyObject *__pyx_k8p;
static PyObject *__pyx_k10p;
static PyObject *__pyx_k12p;
static PyObject *__pyx_k14p;
static PyObject *__pyx_k16p;
static PyObject *__pyx_k18p;
static PyObject *__pyx_k20p;
static PyObject *__pyx_k22p;
static PyObject *__pyx_k24p;
static PyObject *__pyx_k26p;
static PyObject *__pyx_k28p;
static PyObject *__pyx_k30p;
static PyObject *__pyx_k32p;
static PyObject *__pyx_k34p;
static PyObject *__pyx_k36p;
static PyObject *__pyx_k38p;
static PyObject *__pyx_k40p;
static PyObject *__pyx_k42p;
static PyObject *__pyx_k44p;
static PyObject *__pyx_k46p;
static PyObject *__pyx_k48p;
static PyObject *__pyx_k50p;
static PyObject *__pyx_k52p;
static PyObject *__pyx_k54p;
static PyObject *__pyx_k56p;

static __Pyx_InternTabEntry __pyx_intern_tab[] = {
  {&__pyx_n_Cb, "Cb"},
  {&__pyx_n_Cd, "Cd"},
  {&__pyx_n_Cr, "Cr"},
  {&__pyx_n_Tf, "Tf"},
  {&__pyx_n_Tp, "Tp"},
  {&__pyx_n_Yc, "Yc"},
  {&__pyx_n_Yi, "Yi"},
  {&__pyx_n_Ys, "Ys"},
  {&__pyx_n_aa, "aa"},
  {&__pyx_n_ac, "ac"},
  {&__pyx_n_ae, "ae"},
  {&__pyx_n_ai, "ai"},
  {&__pyx_n_an, "an"},
  {&__pyx_n_ap, "ap"},
  {&__pyx_n_ar, "ar"},
  {&__pyx_n_at, "at"},
  {&__pyx_n_au, "au"},
  {&__pyx_n_aw, "aw"},
  {&__pyx_n_ic, "ic"},
  {&__pyx_n_id, "id"},
  {&__pyx_n_ii, "ii"},
  {&__pyx_n_it, "it"},
  {&__pyx_n_pd, "pd"},
  {&__pyx_n_pp, "pp"},
  {&__pyx_n_tabula, "tabula"},
  {&__pyx_n_tabula_antica, "tabula_antica"},
  {&__pyx_n_za, "za"},
  {&__pyx_n_zd, "zd"},
  {&__pyx_n_zm, "zm"},
  {&__pyx_n_zn, "zn"},
  {0, 0}
};

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_k2p, __pyx_k2, sizeof(__pyx_k2)},
  {&__pyx_k4p, __pyx_k4, sizeof(__pyx_k4)},
  {&__pyx_k6p, __pyx_k6, sizeof(__pyx_k6)},
  {&__pyx_k8p, __pyx_k8, sizeof(__pyx_k8)},
  {&__pyx_k10p, __pyx_k10, sizeof(__pyx_k10)},
  {&__pyx_k12p, __pyx_k12, sizeof(__pyx_k12)},
  {&__pyx_k14p, __pyx_k14, sizeof(__pyx_k14)},
  {&__pyx_k16p, __pyx_k16, sizeof(__pyx_k16)},
  {&__pyx_k18p, __pyx_k18, sizeof(__pyx_k18)},
  {&__pyx_k20p, __pyx_k20, sizeof(__pyx_k20)},
  {&__pyx_k22p, __pyx_k22, sizeof(__pyx_k22)},
  {&__pyx_k24p, __pyx_k24, sizeof(__pyx_k24)},
  {&__pyx_k26p, __pyx_k26, sizeof(__pyx_k26)},
  {&__pyx_k28p, __pyx_k28, sizeof(__pyx_k28)},
  {&__pyx_k30p, __pyx_k30, sizeof(__pyx_k30)},
  {&__pyx_k32p, __pyx_k32, sizeof(__pyx_k32)},
  {&__pyx_k34p, __pyx_k34, sizeof(__pyx_k34)},
  {&__pyx_k36p, __pyx_k36, sizeof(__pyx_k36)},
  {&__pyx_k38p, __pyx_k38, sizeof(__pyx_k38)},
  {&__pyx_k40p, __pyx_k40, sizeof(__pyx_k40)},
  {&__pyx_k42p, __pyx_k42, sizeof(__pyx_k42)},
  {&__pyx_k44p, __pyx_k44, sizeof(__pyx_k44)},
  {&__pyx_k46p, __pyx_k46, sizeof(__pyx_k46)},
  {&__pyx_k48p, __pyx_k48, sizeof(__pyx_k48)},
  {&__pyx_k50p, __pyx_k50, sizeof(__pyx_k50)},
  {&__pyx_k52p, __pyx_k52, sizeof(__pyx_k52)},
  {&__pyx_k54p, __pyx_k54, sizeof(__pyx_k54)},
  {&__pyx_k56p, __pyx_k56, sizeof(__pyx_k56)},
  {0, 0, 0}
};

static struct PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

static void __pyx_init_filenames(void); /*proto*/

PyMODINIT_FUNC initcode(void); /*proto*/
PyMODINIT_FUNC initcode(void) {
  PyObject *__pyx_1 = 0;
  __pyx_init_filenames();
  __pyx_m = Py_InitModule4("code", __pyx_methods, 0, 0, PYTHON_API_VERSION);
  if (!__pyx_m) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;};
  Py_INCREF(__pyx_m);
  __pyx_b = PyImport_AddModule("__builtin__");
  if (!__pyx_b) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;};
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;};
  if (__Pyx_InternStrings(__pyx_intern_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;};
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;};

  /* "/home/panx/ouroborus/birdcage/code.pyx":1 */
  __pyx_1 = PyDict_New(); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_Yi, __pyx_k2p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_Yc, __pyx_k4p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_Ys, __pyx_k6p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_Cb, __pyx_k8p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_Cd, __pyx_k10p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_Cr, __pyx_k12p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_Tf, __pyx_k14p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_Tp, __pyx_k16p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_tabula, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/code.pyx":11 */
  __pyx_1 = PyDict_New(); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_ai, __pyx_k18p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_at, __pyx_k20p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_ap, __pyx_k22p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_au, __pyx_k24p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_ic, __pyx_k26p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_ii, __pyx_k28p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_id, __pyx_k30p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_it, __pyx_k32p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_an, __pyx_k34p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_aw, __pyx_k36p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_ar, __pyx_k38p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_ac, __pyx_k40p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_aa, __pyx_k42p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_ae, __pyx_k44p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_zd, __pyx_k46p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_zn, __pyx_k48p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_zm, __pyx_k50p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_za, __pyx_k52p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_pd, __pyx_k54p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyDict_SetItem(__pyx_1, __pyx_n_pp, __pyx_k56p) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_tabula_antica, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 11; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  return;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("code");
}

static char *__pyx_filenames[] = {
  "code.pyx",
};

/* Runtime support code */

static void __pyx_init_filenames(void) {
  __pyx_f = __pyx_filenames;
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
