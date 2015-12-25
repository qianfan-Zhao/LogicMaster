#spi

##lua constants
+ spi mode
    - spi.MODE0
    - spi.MODE1
    - spi.MODE2
    - spi.MODE3
+ spi data order
    - spi.MSBFIRST
    - spi.LSBFIRST
+ token
    - spi.HIGH
    - spi.LOW
    
##lua functions

+ spi.init(mode,order)
+ spi.init(mode,order,bauddiv)
>  **mode**: 用于设置SPI的模式，参数可以是spi.MODE0 ~ spi.MODE3. <br>
> **order**: 可以是spi.MSBFIRST或者spi.LSBFIRST.<br>
> **bauddiv**: 用于设置spi时钟频率。可以是0 ～ 7,分别对应2^0 ~ 2^7分频。这个参数不是必须的。<br>
> *建议在使用spi之前调用一次这个函数。如果你不确定当前spi的模式，可以使用spi.info()函数查看*<br>

+ spi.mode(mode)
+ spi.order(order)
+ spi.div(bauddiv)
> *这三个函数分别用于设置spi的模式，字顺序，时钟分频值。参数请参考spi.init*

+ spi.info()
> *用于获取spi的配置参数。以字符串的形式返回。*

+ spi.dummybyte()
+ spi.dummybyte(byte)
> *用于设置spi的dummybyte。dummybyte是用于spi读取数据的时候，发送到MOSI线上的数据。一般可以是随意数据。根据芯片的不同而要求不同。*<br>
> 当这个函数不指定参数的时候，返回当前的dummybyte。如果指定了byte，那么将dummybyte设置为参数的数值。<br>
> **参数byte必须是0 ～ 255之间的数值**

+ spi.write(write_data,read_num,token, ... )
> *这是一个可变参数的函数，即可以发送数据，又可以读取数据。另外还能用它控制spi的cs信号线（D10）。write_data, read_num, token可以使用任意组合和任意的顺序出现*<br>
> **write_data**:需要使用spi发送的数据。**必须**是0 ~ 255之间的数据。如果大于255,那么只保留最低的一个字节（另外，256表示spi.HIGH,257表示spi.LOW）。不限制发送的个数（*该函数最大的参数个数只与单片机的内存大小相关*）<br>
> **read_num**:需要读取的字节个数。**为了与write_data进行区分，这个参数必须是负数，例如-10表示读取10个字节**。<br>
> **token**:token可以是spi.HIGH或spi.LOW。分别表示将cs拉高和拉低。<br>
> **Example**:拉低cs信号线，发送0x90,0x00,0x00,0x00,之后读取两个字节：<br>
> *spi.write(spi.LOW,0x90,0x00,0x00,0x00,-2,spi.HIGH)*<br>

+ spi.transfer(data_or_token, ... )
> *在发送数据到MOSI的同时，将MISO总线上的数据缓存。在数据全部发送成功之后，返回所有缓存数据。*<br>
> **data_or_token**: 可以是待发送的数据（**必须在0 ～ 255之间**）或者是token。

##Examples
+ 设置spi为模式3,MSBFIRST。
```lua
spi.init(spi.MODE3,spi.MSBFIRST)
```

+ 查看spi当前的模式：
```lua
spi.info()
```
*将会得到类似这样的结果* <br>
*spi freq: 18 MHz, MODE3, MSBFIRST*




