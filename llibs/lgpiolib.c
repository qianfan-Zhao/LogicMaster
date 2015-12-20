#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include <stdio.h>
#include <stdlib.h>

#include "platform.h"
#include "makeparam.h"

/* gpio LIB type,used for create param */
#define GPIO_LIB_TYPE	'g'

#define LGPIO_INPUT    MAKE_P(GPIO_LIB_TYPE,1,GPIO_INPUT)
#define LGPIO_OUTPUT 	 MAKE_P(GPIO_LIB_TYPE,2,GPIO_OUTPUT)
#define LGPIO_ANALOG   MAKE_P(GPIO_LIB_TYPE,3,GPIO_ANALOG)

#define LGPIO_PULLNO   MAKE_P(GPIO_LIB_TYPE,4,GPIO_PULLNO)
#define LGPIO_PULLUP   MAKE_P(GPIO_LIB_TYPE,5,GPIO_PULLUP)
#define LGPIO_PULLDOWN MAKE_P(GPIO_LIB_TYPE,6,GPIO_PULLDOWN)

/**
 ** Lua function: gpio.mode(pin,mode,pull)
 ** mode can be : gpio.INPUT,gpio.OUTPUT,gpio.ANALOG
 ** pin,mode is must.pull is selected
 **/
static int lgpio_mode(lua_State *L)
{
	int pin,mode,paramcount;
	int pull = LGPIO_PULLNO;
	
	paramcount=lua_gettop(L);
	pin=luaL_checkinteger(L,1);
	mode=luaL_checkinteger(L,2);
	if(paramcount>2)
		pull=luaL_checkinteger(L,3);

	if(gpio_mode(pin,P_DATA(mode),P_DATA(pull))){
		lua_pushstring(L,"param error! GPIO.mode(pin,mode)\n");
		lua_error(L);
	}

	return 0; /* lua return value */
}

/**
 ** Lua function: gpio.write(pin,val)
 **/
static int lgpio_write(lua_State *L)
{
	int pin,val;
	pin=luaL_checkinteger(L,1);
	val=luaL_checkinteger(L,2);

	if(gpio_write(pin,val)){
		lua_pushstring(L,"param error! GPIO.write(pin,value) \n");
		lua_error(L);
	}

	return 0;
}

/**
 ** Lua function: gpio.read(pin,...)
 ** This function is a multi-return function.
 ** You can pass all pin's number you want read.(at least one pin)
 ** Note: 
 **  If a pin not a really pin,this function will return -1 as it's value.
 ** Rev: the value of the pin
 **/
static int lgpio_read(lua_State *L)
{
	int i,pin,count;
	int value;
	count = lua_gettop(L);/* all pin's count need read */

	for(i=0;i<count;i++)
	{
		pin=luaL_checkinteger(L,i+1);/* lua index from 1,NOT zero */
		lua_pushinteger(L,gpio_read(pin));
	}
	return i;
}

static int lgpio_toggle(lua_State *L)
{
	int pin=luaL_checkinteger(L,1);
	if(gpio_toggle(pin)){
		lua_pushstring(L,"param not a really pin!\n");
		lua_error(L);
	}
	return 0;
}


/**===============================================
 **/

static const luaL_Reg gpioLib[] = {
    /* function */
    {"mode",lgpio_mode},
    {"write",lgpio_write},
    {"read",lgpio_read},
    {"toggle",lgpio_toggle},

    /* placeholders */
    {"INPUT",NULL},
    {"OUTPUT",NULL},
    {"ANALOG",NULL},
    {"PULLUP",NULL},
    {"PULLDOWN",NULL},
    {NULL,NULL},
};


/**
 **Open gpio lib
 */
LUAMOD_API int luaopen_gpio (lua_State *L)
{
    luaL_newlib(L,gpioLib);

    lua_pushinteger(L,LGPIO_INPUT);
    lua_setfield(L,-2,"INPUT");
    lua_pushinteger(L,LGPIO_OUTPUT);
    lua_setfield(L,-2,"OUTPUT");
    lua_pushinteger(L,LGPIO_ANALOG);
    lua_setfield(L,-2,"ANALOG");
    lua_pushinteger(L,LGPIO_PULLUP);
    lua_setfield(L,-2,"PULLUP");
    lua_pushinteger(L,LGPIO_PULLDOWN);
    lua_setfield(L,-2,"PULLDOWN");

    return 1;
}







