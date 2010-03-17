#include <ruby-ctemplate.h>

static VALUE cCTemplate_initialize(VALUE vself, VALUE vtemplate){
  rb_iv_set(vself, "@template", vtemplate);
  return Qtrue;
}

static VALUE cCTemplate_render(VALUE vself, VALUE vhash){
  VALUE vtemplate, vrendered, vkeys, vkey, vval;
  const char *template_text;
  int num, i;
  Check_Type(vhash, T_HASH);

  vtemplate = rb_iv_get(vself, "@template");
  template_text = (const char*) RSTRING_PTR(vtemplate);
  ctemplate::Template* tpl = ctemplate::Template::StringToTemplate(template_text, ctemplate::DO_NOT_STRIP);

  ctemplate::TemplateDictionary dict("template");

  vkeys = rb_funcall(vhash, rb_intern("keys"), 0);
  num = RARRAY_LEN(vkeys);
  for(i = 0; i < num; i++){
    vkey = rb_ary_entry(vkeys, i);
    vval = rb_hash_aref(vhash, vkey);

    switch(TYPE(vval)){
      case T_STRING:
        dict.SetValue(RSTRING_PTR(vkey), RSTRING_PTR(vval));
        break;
      case T_FIXNUM:
        dict.SetIntValue(RSTRING_PTR(vkey), NUM2INT(vval));
        break;
      default:
        break;
    }
  }

  std::string rendered;
  tpl->Expand(&rendered, &dict);
  vrendered = rb_str_new2(rendered.c_str());
  delete tpl;

  return vrendered;
}

VALUE eCTemplateError;
VALUE cCTemplate;

extern "C" void Init_ctemplate(){
  eCTemplateError = rb_define_class("CTemplateError", rb_eStandardError);
  cCTemplate = rb_define_class("CTemplate", rb_cObject);

  rb_define_private_method(cCTemplate, "initialize", (VALUE(*)(...)) cCTemplate_initialize, 1);
  rb_define_method(cCTemplate, "render", (VALUE(*)(...)) cCTemplate_render, 1);
}
