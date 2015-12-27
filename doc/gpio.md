#LogicMaster gpio guide

```c
/* Left			   NucleoF303RE				   	 Right			
  *                                   15 PB8(SCL)
  *                                   14 PB9(SDA)
  *                                   13 PA5(SCK)
  *                                   12 PA6(MISO)
  *               GPIO                11 PA7(MOSI)
  *           ------------>           10 PB6
  *                |------>            9 PC7
  *                |------>            8 PA9
  *------------------------------------------------
  *   ANALOG       |------>            7 PA8
  *                |------>            6 PB10
  * 16 A0 PA0 <----|------>            5 PB4
  * 17 A1 PA1 <----|------>            4 PB5
  * 18 A2 PA4 <----|------>            3 PB3 
  * 19 A3 PB0 <----|------>            2 PA10
  * 20 A4 PC1 <----|                   1 PA2(Tx)
  * 21 A5 PC0 <----|                   0 PA3(Rx)
  */
```
##gpio pins 

  + digital pins: 2 ~ 10, A0(16) ~ A5(21)
  + analog pins:A0(16) ~ A5(21)
  + SPI pins: 13(SCK), 12(MISO), 11(MOSI)
  + I2C pins: 15(SCL), 14(SDA).
  
##lua constants

  + GPIO/ANALOG pins:
      - gpio.A0 ~ gpio.A5
  + GPIO pin mode:
      - gpio.INPUT
      - gpio.OUTPUT
      - gpio.ANALOG
  + GPIO pin pull
      - gpio.PULLUP
      - gpio.PULLDOWN
      
##lua functions:

+ gpio.mode(pin,mode)
+ gpio.mode(pin,mode,pull)
> **pin** : pin can be selected from 2 ~ 10, or gpio.A0 ~ gpio.A5<br>
> **mode** :mode can be selectd from gpio.INPUT, gpio.OUTPUT, gpio.ANALOG, setting pin as input, output or analog.<br>
> **pull** :pull can be selected from gpio.PULLUP or gpio.PULLDOWN. If not selected, the default 'pull' mode is floating.<br>

+ gpio.write(pin,value)
> **pin** : like gpio.mode's param <br>
> **value** : the actual value you wanted write to this pin. If param 'value' is zero,this function will reset pin. Else(non-zero) will set this pin<br>

+ gpio.read(pin)
+ gpio.read(pin,  ...  )   
 > *read pin's value,and return it. This is a multi-return function in lua. If param 'pin' isn't a valid number,this function will return -1.Else return the actually value on this pin* <br>
 > **pin** :like gpio.mode's param<br>

##examples:

1.**set A0 as INPUT-floating mode,pin4 as OUTPUT-PULLUP mode.**
```lua
gpio.mode(gpio.A0,gpio.INPUT);
gpio.mode(4,gpio.OUTPUT,gpio.PULLUP);
```

2.**read pin3, pin4, pin100's value and print**
```lua
print(gpio.read(3,4,100));
```
*or create three variables saving result*
```lua
a,b,c = gpio.read(3,4,100)
print(a,b,c)
```
*or you can create a table in lua saving multi-return. and print all values in table using 'for'*

```lua
tab={}
tab={gpio.read(3,4,100)}
for i,v in ipairs(tab) do 
  print("pin " ..i.. " 's  value " .. v)
end
```

*will output something like this:*
> pin 3's value 0<br>
> pin 4's value 1<br>
> pin 5's value -1<br>

##gpio引脚
  + 数字引脚：2-10,gpio.A0 ~ gpio.A5
  + 模拟引脚：gpio.A0 ~ gpio.A5
  + SPI 引脚： 13(SCK), 12(MISO), 11(MOSI)
  + I2C 引脚： 15(SCL), 14(SDA).
  
##lua常量
  + GPIO引脚模式:
      - gpio.INPUT
      - gpio.OUTPUT
      - gpio.ANALOG
  + GPIO上/下拉模式
      - gpio.PULLUP
      - gpio.PULLDOWN
      
##lua函数

+ gpio.mode(pin,mode)
+ gpio.mode(pin,mode,pull)
> *用于设置gpio引脚的模式，上/下拉方式*<br>
> **pin**: 可以是2～10, gpio.A0 ~ gpio.A5<br>
> **mode** :模式可以是 gpio.INPUT, gpio.OUTPUT, gpio.ANALOG, 用于设置该引脚是输入，输出或者是模拟输入方式。<br>
> **pull** :上/下拉方式可以是gpio.PULLUP or gpio.PULLDOWN. 如果不指定这个参数的话，默认的方式是无上/下拉，即浮空输入/输出。<br>

+ gpio.write(pin,value)
> *将指定的数值写到指定的引脚上*<br>
> **pin** : 同 gpio.mode <br>
> **value** : 实际需要输出的数值。0表示拉低该引脚。其余的任何非零值都是拉高该引脚。<br>

+ gpio.read(pin)
+ gpio.read(pin,  ...  )   
 >  *读取指定的引脚数值，并返回。不同于c语言，在lua函数中，这是一个多返回值的函数。如果指定的引脚不是gpio引脚，那么该引脚的电平值为-1.否则为实际的电平值。*<br>
 >  **pin**: 请为pin至少指定一个参数。若指定多个pin，那么将会得到多个返回值<br>

##实例：

1.**设置A0为浮空输入，4引脚为上拉输出**
```lua
gpio.mode(gpio.A0,gpio.INPUT);
gpio.mode(4,gpio.OUTPUT,gpio.PULLUP);
```

2.**读引脚3,4,100的电平值，并输出**
```lua
print(gpio.read(3,4,100));
```
*或者创建3个变量来存储*
```lua
a,b,c = gpio.read(3,4,100)
print(a,b,c)
```
*或者创建lua的table来存储多个返回值。并使用‘for’循环打印。*

```lua
tab={}
tab={gpio.read(3,4,100)}
for i,v in ipairs(tab) do 
  print("pin " ..i.. " 's  value " .. v)
end
```

*将会得到类似下面的输出：*
> pin 3's value 0<br>
> pin 4's value 1<br>
> pin 5's value -1<br>

  





