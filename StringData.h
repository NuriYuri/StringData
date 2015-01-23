#define _export __declspec(dllexport)
#define SafeFixnum 0

extern "C" {
	void _export Init_StringData();
}

extern VALUE rb_cStringData;

VALUE StringData_Initialize(VALUE self, VALUE data);
VALUE StringData_getUlong(VALUE self, VALUE pos);
VALUE StringData_setUlong(VALUE self, VALUE pos, VALUE v);

VALUE StringData_getlong(VALUE self, VALUE pos);
VALUE StringData_setlong(VALUE self, VALUE pos, VALUE v);

VALUE StringData_getUshort(VALUE self, VALUE pos);
VALUE StringData_setUshort(VALUE self, VALUE pos, VALUE v);

VALUE StringData_getshort(VALUE self, VALUE pos);
VALUE StringData_setshort(VALUE self, VALUE pos, VALUE v);

VALUE StringData_getUbyte(VALUE self, VALUE pos);
VALUE StringData_setUbyte(VALUE self, VALUE pos, VALUE v);

VALUE StringData_getbyte(VALUE self, VALUE pos);
VALUE StringData_setbyte(VALUE self, VALUE pos, VALUE v);

VALUE StringData_getfloat(VALUE self, VALUE pos);
VALUE StringData_setfloat(VALUE self, VALUE pos, VALUE v);

VALUE StringData_getdouble(VALUE self, VALUE pos);
VALUE StringData_setdouble(VALUE self, VALUE pos, VALUE v);

VALUE StringData_getstring(VALUE self, VALUE pos, VALUE len);
VALUE StringData_setstring(VALUE self, VALUE pos, VALUE v);


#if SafeFixnum == 1
#define test_fix(arg) rb_check_type(arg,T_FIXNUM)
#else
#define test_fixnum(arg)
#endif

#define check_pos(self, pos, _pos, add) \
	test_fixnum(pos); \
    _pos = FIX2LONG(pos); \
	if (_pos < 0) \
		{ \
		_pos += RSTRING_LEN(self); \
		if (_pos < 0) \
			rb_raise(rb_eArgError, "Negative Overflow."); \
		} \
	\
	if ((long)(_pos + add)>(long)RSTRING_LEN(self)) \
		rb_raise(rb_eArgError, "Overflow.");

#define get_string_data_ptr(type, self, pos) \
	long _pos; \
    type* data; \
    check_pos(self, pos, _pos, sizeof(type)); \
    data = (type*)(_pos + (long)RSTRING_PTR(self));

#define create_string_data_getter_body(name, type, ruby_meth) \
VALUE name(VALUE self, VALUE pos) \
{ \
	get_string_data_ptr(type, self, pos); \
	return ruby_meth(*data); \
}

#define create_string_data_setter_body(name, type,ruby_meth) \
VALUE name(VALUE self, VALUE pos, VALUE v) \
{ \
	get_string_data_ptr(type, self, pos); \
	*data = (type)ruby_meth(v); \
	return self; \
}

#define create_string_data_setter_body_f(name, type,ruby_meth) \
VALUE name(VALUE self, VALUE pos, VALUE v) \
{ \
	get_string_data_ptr(type, self, pos); \
	rb_check_type(v,T_FLOAT); \
	*data = (type)ruby_meth(v); \
	return self; \
}
