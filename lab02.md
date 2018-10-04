# 利用construct2工具来制作一个简单的小游戏——飞机大战
## 同学们，你们初入计算机世界，有没有制作小游戏的想法呢？？不会做？？不要紧，这里就是飞机大战的制作教程！！
我们先来看一下这效果图

<div align="center"><img src="http://m.qpic.cn/psb?/V1163ODP3Tjsyo/.gEq7nA8YuNf8SzEHlfhDHUSDuiuuGnV6TfNFxeKR7Q!/b/dFMBAAAAAAAA&bo=ygEXAQAAAAACd44!&rf=viewer_4"></div>

## 接下来，就是我们的具体教程了！
### 首先打开construct2，做好必要的文件准备。
1、如果没有construct2，可在https://www.scirra.com上下载

2、打开construrt2,选择new project
<img src="images/0 (49).png">

3、建立空项目，new empty project
<img src="images/0 (48).png">

4、看到中间空白的长方形，虚线是运行时所能看到的（可以点击右上new project后左边的Windows size调整），现在可以在里面添加背景了，双击空白处,选择tiled background
<img src="images/0 (47).png">

5、之后弹出一个窗口，选择左上角的文件夹，选择你想添加的背景
<img src="images/0 (46).png">

6、选择后你的背景将会出现，手动拉伸，并将它们的position调整为0，0。并且按照个人喜欢调整size
<img src="images/0 (45).png">
<img src="images/0 (44).png">

7、现在要将图层锁定，将0图层改名并锁定，然后添加一个main的图层
<img src="images/0 (43).png"><img src="images/0 (42).png">

8、现在要添加其他东西，方法与刚才一样，不同的是tiled background换成sprite。（为避免出现不想要的结果，将爆炸和子弹拉出背景外）
<img src="images/0 (41).png"><img src="images/0 (40).png">
好了现在文件都已经插入了。

### 现在就要给他们插入事件了
1、我们先给飞机一个behavior，右下方右击飞机，点击behaviors，选择8-diretions。然后关闭窗口即可。现在我们就可以通过键盘方向键来控制飞机方向啦！
<img src="images/0 (39).png">
<img src="images/0 (38).png">

2、飞机都能动了，下一个肯定是怪物啦！现在我们同样给怪物一个behaviors，但是选择bullet，意思就是像子弹一样走啦，玩家可以自己在左方的speed改变monster的速度。同时按Ctrl拉动monster可添加多个monster。
<img src="images/0 (37).png">
<img src="images/0 (36).png">

3、现在要添加外部硬件了，我们在这里添加鼠标（键盘已经自动嵌入）
<img src="images/0 (35).png">

4、现在要让他们做事情了！添加活动！在event sheet1中add event,首先选择add system，选择every tick<img src="images/0 (34).png"><img src="images/0 (33).png">
再add action，选择set angle toward position并如图所示输入XY，现在飞机方向就可以由鼠标控制了！<img src="images/0 (32).png"><img src="images/0 (31).png">

5、现在就要用鼠标发射子弹了，再一次add action，选择mouse，on click,spawn another object,选择bullet，layer 1.<img src="images/0 (30).png"><img src="images/0 (29).png"><img src="images/0 (28).png"><img src="images/0 (27).png">现在飞机就可以发射子弹啦！

2、那光打子弹没用啊，子弹要有威力才行，这里就给子弹添加碰撞爆炸的特效。对bullet添加事件，选择on collision with other object，再选spawn another object,再选择explore,这样子在子弹碰到怪物后就会触发爆炸效果。注意，explore的左边blend mode要选择additive，不然爆炸会很难看哦。我们还可以设置子弹碰到怪物后怪物消失，所以在explore后面继续add action，让怪物destory。
<img src="images/0 (26).png">
<img src="images/0 (25).png">
<img src="images/0 (24).png">
<img src="images/0 (23).png">
<img src="images/0 (22).png">

3、我们不能让自己无敌吧，无敌多没意思，现在我们就设置我们不能碰到怪物。与上面相似，对象是飞机，on collision with another object，飞机destory，由于与monster极度相似，这里就不详细讲了。
<img src="images/0 (20).png">

4、现在我们就要monster动起来了！再次add event，对象是monster，因为从一开始就动所以选择on the start of layout,set angle,如图输入random(360)，这样怪物就会开始随机走了。
<img src="images/0 (19).png">
<img src="images/0 (18).png">
<img src="images/0 (16).png">

5、可是仅做到第4步monster走出去边缘了就不会走回来了，现在我们就给他画一个边缘。对象是monster，add event，选择is outside the layout，再从add action里选择set
angle toward position,设置为撞墙后朝向飞机，所以XY如图所示。
<img src="images/0 (15).png">
<img src="images/0 (14).png">

6、现在我们还要限制住飞机不能出去，只需要给飞机添加两个behaviors就可以了。
<img src="images/0 (13).png">

7、其实现在游戏已经可以开始玩了，可是为了增加娱乐性，我们不要monster一枪死，所以我们在右下方右击他选择instance variable给他定义一个变量：“血量”5，然后把一开始子弹碰撞后的destroy delete 改成subtract 1 from 血量。
<img src="images/0 (12).png"><img src="images/0 (50).png">

8、我们再add event，对象是monster，选择compare instance variable，设置当小于等于零时，monster被destroy
<img src="images/0 (11).png">

9、现在我们再引入一个分数score，在event sheet空白处右击鼠标，添加全局变量，add global variable score=0，然后将原来的图层锁定，再添加一个新图层并命名为score，然后在背景处双击,添加一个text，这个text即为score，
<img src="images/0 (10).png">
<img src="images/0 (5).png">

10、再从monster destroy后add action，选择system，add to 1，让每打死一个monster就加一分。<img src="images/0 (9).png"><img src="images/0 (8).png"><img src="images/0 (7).png">

11、来到最后，我们要添加一个结束语，失败了就会出现。首先再次添加图层，并将其他图层锁定。在新图层双击左键添加一个text,在左边方框可以修改相关属性如名称颜色字体大小等。并且一开始要在左侧initial visibility设置为invisible<img src="images/0 (4).png">
<img src="images/0 (3).png">

12、最后的最后，在飞机destroy后加一个action，选择text 3，选择visible。这样当飞机摧毁后你的结束语句就会出现了。

##这就是飞机大战的教程了！尝试着制作这个游戏，体验制作游戏的乐趣吧！

