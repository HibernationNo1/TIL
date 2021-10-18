# MainWindow

new project > WPF app(.NET Framework) >  이름, 위치 결정 후 framework는 .NET Framework 4.7.2



```
<Window x:Class="projecct_0.MainWindow"
        xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
        xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
        xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
        xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
        xmlns:local="clr-namespace:projecct_0"
        mc:Ignorable="d"
        Title="MainWindow" Height="450" Width="800">

</Window>
```



**Contral할당**

```xaml
<Grid>
	<local:UserContral_1/>
</Grid>
```

> local에 정의된 UserContral_1이라는 이름의 xaml file을 load