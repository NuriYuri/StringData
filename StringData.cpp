// StringData.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "StringData.h"

VALUE rb_cStringData = NULL;

void _export Init_StringData()
{
	VALUE Yuki;
	ID Yuki_id = rb_intern("Yuki");

	//Récupération du module Yuki
	if (rb_const_defined(rb_cObject, Yuki_id))
		Yuki = rb_const_get(rb_cObject, Yuki_id);
	else
		Yuki = rb_define_module_under(rb_cObject, "Yuki");

	//Création de la classe
	rb_cStringData = rb_define_class_under(Yuki, "StringData", rb_cString);
	
	//Création du constructeur
	rb_define_method(rb_cStringData, "initialize", _rbf StringData_Initialize, 1);

	//Définition des fonctions
	rb_define_method(rb_cStringData, "ulong", _rbf StringData_getUlong, 1);
	rb_define_method(rb_cStringData, "set_ulong", _rbf StringData_setUlong, 2);

	rb_define_method(rb_cStringData, "long", _rbf StringData_getlong, 1);
	rb_define_method(rb_cStringData, "set_long", _rbf StringData_setlong, 2);

	rb_define_method(rb_cStringData, "ushort", _rbf StringData_getUshort, 1);
	rb_define_method(rb_cStringData, "set_ushort", _rbf StringData_setUshort, 2);

	rb_define_method(rb_cStringData, "short", _rbf StringData_getshort, 1);
	rb_define_method(rb_cStringData, "set_short", _rbf StringData_setshort, 2);

	rb_define_method(rb_cStringData, "ubyte", _rbf StringData_getUbyte, 1);
	rb_define_method(rb_cStringData, "set_ubyte", _rbf StringData_setUbyte, 2);

	rb_define_method(rb_cStringData, "byte", _rbf StringData_getbyte, 1);
	rb_define_method(rb_cStringData, "set_byte", _rbf StringData_setbyte, 2);

	rb_define_method(rb_cStringData, "float", _rbf StringData_getfloat, 1);
	rb_define_method(rb_cStringData, "set_float", _rbf StringData_setfloat, 2);

	rb_define_method(rb_cStringData, "double", _rbf StringData_getdouble, 1);
	rb_define_method(rb_cStringData, "set_double", _rbf StringData_setdouble, 2);

	rb_define_method(rb_cStringData, "string", _rbf StringData_getstring, 2);
	rb_define_method(rb_cStringData, "set_string", _rbf StringData_setstring, 2);
}

//---
//Initialisation d'un objet StringData
//---
VALUE StringData_Initialize(VALUE self, VALUE data)
{
	rb_check_type(data, T_STRING);
	rb_str_concat(self, data);
	return self;
}

//---------------------//
//---- Partie Long ----//
//---------------------//
create_string_data_getter_body(StringData_getUlong, unsigned long, rb_uint2inum)
create_string_data_setter_body(StringData_setUlong, unsigned long, rb_num2ulong)
create_string_data_getter_body(StringData_getlong, long, rb_int2inum)
create_string_data_setter_body(StringData_setlong, long, rb_num2long)


//----------------------//
//---- Partie Short ----//
//----------------------//
create_string_data_getter_body(StringData_getUshort, unsigned short, rb_uint2inum)
create_string_data_setter_body(StringData_setUshort, unsigned short, rb_num2ushort)
create_string_data_getter_body(StringData_getshort, short, rb_int2inum)
create_string_data_setter_body(StringData_setshort, short, rb_num2short)


//---------------------//
//---- Partie Byte ----//
//---------------------//
create_string_data_getter_body(StringData_getUbyte, unsigned char, rb_uint2inum)
create_string_data_setter_body(StringData_setUbyte, unsigned char, rb_num2ushort)
create_string_data_getter_body(StringData_getbyte, char, rb_int2inum)
create_string_data_setter_body(StringData_setbyte, char, rb_num2short)


//-----------------------//
//---- Partie Réelle ----//
//-----------------------//
VALUE StringData_getfloat(VALUE self, VALUE pos)
{ 
	get_string_data_ptr(float, self, pos);
	return rb_float_new((double)(*data));
}
create_string_data_setter_body_f(StringData_setfloat, float, rb_float_value)
create_string_data_getter_body(StringData_getdouble, double, rb_float_new)
create_string_data_setter_body_f(StringData_setdouble, double, rb_float_value)


//-----------------------//
//---- Partie String ----//
//-----------------------//
VALUE StringData_getstring(VALUE self, VALUE pos, VALUE len)
{
	long _pos;
	char* data;
	long _len = rb_num2long(len);
	VALUE str = rb_str_new(NULL, _len);
	check_pos(self, pos, _pos, _len);
	data = (char*)(_pos + (long)RSTRING_PTR(self));
	memcpy(RSTRING_PTR(str), data, _len);
	return str;
}

VALUE StringData_setstring(VALUE self, VALUE pos, VALUE v)
{
	long _pos; 
	char* data;
	rb_check_type(v, T_STRING);
	check_pos(self, pos, _pos, RSTRING_LEN(v)); 
	data = (char*)(_pos + (long)RSTRING_PTR(self));
	memcpy(data, RSTRING_PTR(v), RSTRING_LEN(v));
	return self;
}
