# Contral

project에서 우클릭 > 추가 > 새 항목 > 페이지(WPF) > 이름 : Usercontral_1



#### base knowledge

Contral이란 특정 기능을 구현하는 하나의 function으로 이해하면 되며 기본 형태는 open과 close로 구성되어 있다.

또한 Contral안에는 다시 Contral을 선언할 수 있다.

```xaml
<Grid></Grid>
또는
<Grid/>
```

> Grid contral
>
> open : `<Grid>`
>
> close : `</Grid>`

각 Contral에는 추가 properties를 제공할 수 있는 parameter를 추가할 수 있다.

```xaml
<Border Padding="10" Background="DarkViolet">
</Border>
```

> Border에 Padding과 Background라는 attribute를 추가

 

기본 제공 WPF 컨트롤은 다음과 같다.

- **단추**: [Button](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.button) 및 [RepeatButton](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.primitives.repeatbutton)
- **데이터 표시**: [DataGrid](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.datagrid), [ListView](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.listview) 및 [TreeView](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.treeview).
- **날짜 표시 및 선택**: [Calendar](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.calendar) 및 [DatePicker](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.datepicker)
- **대화 상자**: [OpenFileDialog](https://docs.microsoft.com/ko-kr/dotnet/api/microsoft.win32.openfiledialog), [PrintDialog](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.printdialog)및 [SaveFileDialog](https://docs.microsoft.com/ko-kr/dotnet/api/microsoft.win32.savefiledialog)
- **디지털 잉크**: [InkCanvas](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.inkcanvas) 및 [InkPresenter](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.inkpresenter)
- **문서**: [DocumentViewer](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.documentviewer), [FlowDocumentPageViewer](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.flowdocumentpageviewer), [FlowDocumentReader](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.flowdocumentreader), [FlowDocumentScrollViewer](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.flowdocumentscrollviewer)및 [StickyNoteControl](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.stickynotecontrol)
- **입력**: [TextBox](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.textbox), [RichTextBox](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.richtextbox)및 [PasswordBox](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.passwordbox)
- **레이아웃**: [Border](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.border), [BulletDecorator](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.primitives.bulletdecorator), [Canvas](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.canvas), [DockPanel](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.dockpanel), [Expander](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.expander), [Grid](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.grid), [GridView](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.gridview), [GridSplitter](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.gridsplitter), [GroupBox](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.groupbox), [Panel](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.panel), [ResizeGrip](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.primitives.resizegrip), [Separator](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.separator), [ScrollBar](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.primitives.scrollbar), [ScrollViewer](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.scrollviewer), [StackPanel](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.stackpanel), [Thumb](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.primitives.thumb), [Viewbox](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.viewbox), [VirtualizingStackPanel](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.virtualizingstackpanel), [Window](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.window)및 [WrapPanel](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.wrappanel)
- **미디어**: [Image](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.image), [MediaElement](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.mediaelement)및 [SoundPlayerAction](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.soundplayeraction)
- **메뉴**: [ContextMenu](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.contextmenu), [Menu](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.menu)및 [ToolBar](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.toolbar)
- **탐색**: [Frame](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.frame), [Hyperlink](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.documents.hyperlink), [Page](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.page), [NavigationWindow](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.navigation.navigationwindow)및 [TabControl](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.tabcontrol)
- **선택**: [CheckBox](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.checkbox), [ComboBox](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.combobox), [ListBox](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.listbox), [RadioButton](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.radiobutton)및 [Slider](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.slider)
- **사용자 정보**: [AccessText](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.accesstext), [Label](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.label), [Popup](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.primitives.popup), [ProgressBar](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.progressbar), [StatusBar](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.primitives.statusbar), [TextBlock](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.textblock)및 [ToolTip](https://docs.microsoft.com/ko-kr/dotnet/api/system.windows.controls.tooltip)



## Layout

#### Grid

Layout개념으로 flexible한 Grid영역을 define한다. (그릇)



##### Grid.contral

- `Grid.RowDefinitions` : difined Grid영역에서 Row방향으로 나누어 사용할 수 있도록 한다.
  - `RowDefinition` : 사용할 Row Grid의 instance
    - `Height`

- `Grid.ColumnDefinitions` : difined Grid영역에서 Column방향으로 나누어 사용할 수 있도록 한다.

  - `ColumnDefinition` : 사용할 Column Grid의 instance
    - `Width`

  ```xaml
          <Grid >
              <Grid.RowDefinitions>
                  <RowDefinition Height="100"/>		
                  <RowDefinition Height="20"/>
                  <RowDefinition/>
              </Grid.RowDefinitions>
              <Grid.ColumnDefinitions>
                  <ColumnDefinition />
                  <ColumnDefinition />
              </Grid.ColumnDefinitions>
  		</Grid>
  ```

  > Grid영역을 3개의 Row와 2개의 Column으로 나누었다. Height를 설정하지 않으면 알아서 영역을 채우는 크기로 결정된다.



- `width`
- `height`
- `Margin` : contral의 위치 (x_min, y_min, width - x_max, height - y_max)





#### Border

Layout의 padding, background와 같은 properties를 설정하는데 사용한다.

[color](https://somgle.tistory.com/123)



- image에 CornerRadius적용

  ```
  <Border Grid.Row="0" Height="150" CornerRadius="10, 10, 0, 0">
  	<Border.Background>
  		<ImageBrush Stretch="Fill" ImageSource="vscodejpg.jpg"  />
  	</Border.Background>
   </Border>
  ```

  > Border Grid.Row="0" 에 속한 ImageBrush는  CornerRadius="10, 10, 0, 0"를 따른다.
  >
  > 만일 <images>라면 CornerRadius를 따르지 않는다.



- `Padding`

- `Background` : background 색상 

- `CornerRadius` : layout의 각 edge의 굴곡 결정 (좌측 위 부터 시계방향 4개의 element)

  ```
  <Border CornerRadius="4,4,0,0">
  ```




#### StackPanel

여러개의 contral를 쌓는데 사용하는 layout

```
<StackPanel Orientation="Vertical">
	<TextBlock Text = "어떤 종류의 커피를 드시겠습니까?" Margin="30, 30" FontSize="20"/>
                <Button Margin="20">아이스 아메리카노</Button>
                <Button Margin="20">카페모카</Button>
                <Button Margin="10">돌체라떼</Button>
                <Button Margin="10">카푸치노</Button>
	</StackPanel>
```



- `Orientation` = Horizontal :  가로로 정렬,   = Vertical : 세로로 정렬

  StackPanel 안에서는 주로 Margin을 통해 간격을 설정함



#### WrapPanel

StackPanel과 비슷하지만, 칸의 허용범위에 넘어가면 다음 칸으로 넘어가서 생성됨

```
<WrapPanel Orientation="Vertical">
	<TextBlock Margin="30, 30" FontSize="20">어떤 종류의 커피를 드시겠습니까?</TextBlock>
    <Button Margin="20">아이스 아메리카노</Button>
    <Button Margin="20">카페모카</Button>
</WrapPanel>
```



- `Orientation`



#### ListView

여러 값을 list형태로 나열할 때 사용



- ` <ListView.View>`

  ```
  <ListView Grid.Column="1"  FontSize="30" >
       <ListView.View>
       	<GridView>
       		<GridViewColumn Header="name" DisplayMemberBinding="{Binding name}" />
       		<GridViewColumn Header="name" DisplayMemberBinding="{Binding name}"/>
       		<GridViewColumn Header="name" DisplayMemberBinding="{Binding name}" />
        		<GridViewColumn Header="name" DisplayMemberBinding="{Binding name}" />
       	</GridView>
       </ListView.View>
  </ListView>
  ```

  > ListView선언 후 ListView.View를 통해 영역을 만들고 GridView로 영역에 grid 속성 적용하도록 만듬
  >
  > - GridViewColumn의 속성
  >   - `Header` : 입력할 text
  >   - `DisplayMemberBinding` : 불러올 data

- `<ListViewItem>`

  

- `<ListView.ItemTemplate>`

  

  





- `FontSize` 및 관련된것 있음

- `Background`





## Button

#### Button

- `Content` : button의 text표현

- `HorizontalContentAlignment` : button의 수평 영역 지정
  - `Stretch` : 영역의 전체 
  - `center` 
  - `left`
  - `right`
- `VerticalAlignment`: button의 수직 영역 지정
- `Background`
- `Click` : 버튼이 눌리면 호출할 (C code behind에서 작성된)함수를 할당
- `FontSize`
- `FontWeight`
- `Foreground`





- `Button.Resources` : button의 CornerRadius지정

  ```
  <Button.Resources>
  	<Style TargetType="Border">
  		<Setter Property="CornerRadius" Value="5, 0, 0, 5"/>
  	</Style>
  </Button.Resources>
  ```










## Image

**image 삽입 방법**

`<Image>` 의 property > 공용 > source의 '기존항목추가' 버튼 > image선택 

 `<Image>` 의 `Source = "path"`에 입력

```
<Image Grid.Column="0" Source="acount_.png" />
```





## Text

#### Textbox

내용을 설명해주는 등 일반적인 효과 없는 text를 출력할 때 사용

```
<TextBox TextWrapping="Wrap" Text="TextBox"/>
```



- `Text`

- `TextWrapping` : 



#### TextBlock

Textbox와 다른점 : 다양한 color, fontsize, fonttype 설정 등 문자의 rendering이 가능

시각적으로 보는데 집중시킬 때 사용

```
<TextBlock Grid.Row="0" Text="Material Desing" FontSize="30" Foreground="White"
                                       VerticalAlignment="Center" HorizontalAlignment="Left"/>
```



- `Text`
- `HorizontalAlignment` : 수평위치
- `VerticalAlignment` : 수직위치
- `FontSize`
- `FontWeight`



#### Label

text대신 Content속성을 사용해서 text를 표현한다.

TextBlock과의 차이점 : 단지 text가아니라 모든 종류의 contral을 직접 hosting이 가능하다.

> 테두리 지정 가능
>
> 다른 contral rendering가능
>
> 

```
<Grid>
	<Label Content="This is a Label control." />
</Grid>
```

 



## shape

### Rectangle

draw rectangle



### Ellipse

circle을 그리는 contral

```
<Border Background="LightGray" CornerRadius="100, 100, 100, 100">
    <Ellipse Width="73" Height="73">		
        <Ellipse.Fill>
            <ImageBrush ImageSource="1606648454554.jpg" />
        </Ellipse.Fill>
    </Ellipse>
</Border>
```

> Border에 CornerRadius="100, 100, 100, 100" 을 줘서 원으로 만들고,
>
> Width="73" Height="73" 인 circle그린 후 1606648454554.jpg라는 image로 내부를 채움
>
> 2개의 circle생성





