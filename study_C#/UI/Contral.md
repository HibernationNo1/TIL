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





#### Border

Layout의 padding, background와 같은 properties를 설정하는데 사용한다.

[color](https://somgle.tistory.com/123)





### property

- `Padding`

- `Background` : background 색상 

- `CornerRadius` : layout의 각 edge의 굴곡 결정 (좌측 위 부터 시계방향 4개의 element)

  ```
  <Border CornerRadius="4,4,0,0">
  ```

- 







## Button

#### Button

- `Button.Resources` : button의 CornerRadius지정

  ```
  <Button.Resources>
  	<Style TargetType="Border">
  		<Setter Property="CornerRadius" Value="5, 0, 0, 5"/>
  	</Style>
  </Button.Resources>
  ```

  

#### 



### property

- `HorizontalContentAlignment` : button의 수평 영역 지정
  - `Stretch` : 영역의 전체 
  - `center` 
  - `left`
  - `right`
- VerticalAlignment : button의 수직 영역 지정
- `Background`





## Image

**image 삽입 방법**

`<Image>` 의 property > 공용 > source의 '기존항목추가' 버튼 > image선택 

 `<Image>` 의 `Source = "path"`에 입력

```
<Image Grid.Column="0" Source="acount_.png" />
```





## Text

#### TextBlock



### property

- `Text`
- `HorizontalAlignment` : 수평위치
- `VerticalAlignment` : 수직위치
- `FontSize`
- `FontWeight`



## shape

### rectangle



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





