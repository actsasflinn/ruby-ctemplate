#ifndef RUBY_CTEMPLATE
#define RUBY_CTEMPLATE

#include <ruby.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <ctemplate/template.h>

#if !defined(RSTRING_PTR)
#define RSTRING_PTR(TC_s) (RSTRING(TC_s)->ptr)
#endif
#if !defined(RSTRING_LEN)
#define RSTRING_LEN(TC_s) (RSTRING(TC_s)->len)
#endif
#if !defined(RARRAY_LEN)
#define RARRAY_LEN(TC_a) (RARRAY(TC_a)->len)
#endif

extern "C" VALUE eCTemplateError;
extern "C" VALUE cCTemplate;

//static VALUE cCTemplate_initialize(VALUE vself, VALUE vtemplate);
//static VALUE cCTemplate_render(VALUE vself);

extern "C" void Init_ctemplate();

#endif
