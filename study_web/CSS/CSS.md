# CSS

CSS(Cascading Style Sheets)는 HTML 요소에 스타일을 적용하는 언어.

HTML은 웹 페이지의 구조와 콘텐츠를 정의하고, CSS는 그 구조와 콘텐츠의 시각적 표현을 정의한다.



## CSS 작성

CSS 규칙은 선택자와 중괄호 `{}`로 시작하며, 중괄호 안에 속성과 값을 쌍으로 지정한다.

```
선택자 {
    속성: 값;
    속성: 값;
    ...
}
```

- **선택자(Selector)**:
  - 선택자는 스타일을 적용할 HTML 요소를 지정한다.
  - 예: `p`, `.classname`, `#idname`, `div > p`, `a:hover`
- **속성(Property)**:
  - 스타일의 특정 측면을 정의한다.
  - 예: `color`, `font-size`, `margin`, `padding`, `background`
- **값(Value)**:
  - 속성에 대해 설정할 구체적인 값을 지정한다.
  - 예: `red`, `16px`, `10px`, `auto`, `url('image.jpg')`

> 예시
>
> ```
> /* 모든 p 요소의 텍스트 색상을 빨간색으로 설정 */
> p {
>     color: red;
> }
> 
> /* id가 header인 요소의 배경색을 파란색으로 설정 */
> #header {
>     background-color: blue;
> }
> 
> /* class가 container인 요소의 패딩을 20px로 설정 */
> .container {
>     padding: 20px;
> }
> ```



### Property

모든 요소에 적용될 수 있는 일반적인 CSS 속성

#### 공통

- **display**: 요소의 박스 타입을 결정한다.

  - **`block`**
    - 요소를 블록 레벨 요소로 설정
    - 블록 레벨 요소는 항상 새로운 줄에서 시작하며, 가로 방향으로 가능한 모든 공간을 차지한다.
    - 예: `<div>`, `<p>`, `<h1>`, `<section>`
  - **`inline`**
    - 요소를 인라인 요소로 설정
    - 인라인 요소는 줄바꿈 없이 다른 요소와 같은 줄에 배치된다.
    - 예: `<span>`, `<a>`, `<strong>`
  - **`flex`**
    - 요소를 Flexbox 컨테이너로 설정
    - 자식 요소들을 유연하게 배치하고 정렬할 수 있는 강력한 레이아웃 모델
    - 예: `<div style="display: flex;">`
  - **`grid`**
    - 요소를 Grid 컨테이너로 설정합니다.
    - 자식 요소들을 행과 열로 구성된 그리드 레이아웃에 배치할 수 있다.
    - 예: `<div style="display: grid;">`

- **position**: 요소의 위치를 결정한다.

  - **`static`**

    - 기본값으로, 요소는 문서의 일반적인 흐름에 따라 배치된다.
    - `top`, `right`, `bottom`, `left`, `z-index` 속성은 무시된다.
    - 예: 기본적으로 모든 HTML 요소는 `position: static;` 임

  - **`relative`**

    - 요소를 원래 위치를 기준으로 상대적으로 배치된다.

    - 요소는 문서의 일반적인 흐름에 따라 배치되지만, `top`, `right`, `bottom`, `left` 속성을 사용하여 원래 위치에서 이동할 수 있다.

      ```
      .relative-box {
          position: relative;
          top: 10px; /* 원래 위치에서 10픽셀 아래로 이동 */
          left: 20px; /* 원래 위치에서 20픽셀 오른쪽으로 이동 */
      }
      ```

    - 원래 위치는 공간을 차지한 상태로 남아 있게된다.

  - **`absolute`**

    - 요소를 가장 가까운 위치 조상 요소를 기준으로 절대적으로 배치된다. 위치 조상 요소가 없으면 `body`를 기준으로 한다.
    - 문서의 일반적인 흐름에서 제거되며, 다른 요소는 이 요소가 차지했던 공간을 무시한다.
    - `top`, `right`, `bottom`, `left` 속성을 사용하여 위치를 지정할 수 있다.

  - **`fixed`**

    - 요소를 뷰포트를 기준으로 고정된 위치에 배치한다. 스크롤해도 요소의 위치가 변하지 않는다.
    - 문서의 일반적인 흐름에서 제거되며, 다른 요소는 이 요소가 차지했던 공간을 무시한다.
    - `top`, `right`, `bottom`, `left` 속성을 사용하여 위치를 지정할 수 있다.

- **z-index**: 요소의 쌓임 순서를 결정한다. `position`이 `relative`, `absolute`, `fixed`, `sticky`일 때만 의미가 있다.

- **width**, **height**: 요소의 너비, 높이를 설정한다.

- **margin**, **padding**: 요소의 외부, 내부 여백을 설정한다. (모든 방향)

  특정 방향에 대한 설정은 아래 속성을 사용

  - margin-bottom, padding-bottom
  - margin-top, padding-top
  - margin-right, padding-right
  - margin-left, padding-left

- **border**: 요소의 테두리를 설정

  - **border-style**: 속성은 요소의 테두리 스타일을 설정
    - `none`: 테두리가 없음
    - `solid`: 단색의 실선
    - `dotted`: 점선
    - `dashed`: 대시(짧은 선)
    - `double`: 이중선
    - `groove`: 테두리가 홈이 파인 것처럼 보임
    - `ridge`: 테두리가 돌출된 것처럼 보임
    - `inset`: 테두리가 요소 안쪽으로 들어간 것처럼 보임
    - `outset`: 테두리가 요소 바깥쪽으로 돌출된 것처럼 보임
  - **border-radius**: 요소의 테두리를 둥글게 만들 때 사용 (단위: `px`)
  - **border-style**: 속성은 요소의 테두리 스타일을 설정
  - **border-color**

- **cursor**: 마우스 포인터가 요소 위에 있을 때의 커서 모양을 설정

  - `default`: 기본 포인터
  - `pointer`: 손가락 모양 (링크 또는 클릭 가능한 버튼에 주로 사용)
  - `text`: 텍스트 선택 커서 (텍스트 입력 필드나 텍스트 영역에 주로 사용)
  - `move`: 이동 커서
  - `wait`: 대기 중 커서
  - `crosshair`: 십자선 모양
  - `not-allowed`: 금지된 커서

- **background**: 요소의 배경을 설정

  - 예: `background-color`, `background-image`.

- **color**: 텍스트 색상을 설정

- **font**: 텍스트의 폰트 관련 속성을 설정

  - 예: `font-size`, `font-family`, `font-weight`.

- **text-align**: 텍스트 정렬을 설정

  - 예: `left`, `right`, `center`, `justify`.

- **visibility**: 요소의 가시성을 설정

  - 예: `visible`, `hidden`.

- **opacity**: 요소의 투명도를 설정

  - 예: `0` (완전히 투명), `1` (완전히 불투명).

- **overflow**: 요소의 콘텐츠가 요소의 지정된 크기를 초과할 때 어떻게 처리할지를 정의한다.

  **overflow-y**: 요소의 수직 방향 콘텐츠가 요소의 지정된 높이를 초과할 때 어떻게 처리할지를 정의

  **overflow-x**: 요소의 수평 방향 콘텐츠가 요소의 지정된 길이를 초과할 때 어떻게 처리할지를 정의

  - **`visible`**: 기본값으로, 초과된 콘텐츠가 잘리지 않고 요소 밖으로 표시된다.
  - **`hidden`**: 초과된 콘텐츠가 잘리고 표시되지 않는다.
  - **`scroll`**: 초과된 콘텐츠가 잘리며, 스크롤 바가 추가되어 스크롤할 수 있다.
  - **`auto`**: 초과된 경우에만 스크롤 바가 추가된다.

- **transition**: CSS 속성 값의 변화에 애니메이션 효과를 추가

  - **`property`**: 애니메이션 효과를 적용할 CSS 속성. 

    - `width`: 요소의 너비가 변경될 때 애니메이션 효과가 적용된다.

      `.box` 요소에 마우스를 올리면 `width` 속성이 100px에서 200px로 0.5초 동안 부드럽게 전환 예제

      ```
      .box {
          width: 100px;
          height: 100px;
          background-color: blue;
          transition: width 0.5s ease;
      }
      
      .box:hover {
          width: 200px;
      }
      ```

    -  `height`: 요소의 높이가 변경될 때 애니메이션 효과가 적용된다.

    -  `background-color`: 요소의 배경색이 변경될 때 애니메이션 효과가 적용된다.

       `.box` 요소에 마우스를 올리면 `background-color` 속성이 파란색에서 빨간색으로 0.5초 동안 부드럽게 전환 예제

      ```
      .box {
          width: 100px;
          height: 100px;
          background-color: blue;
          transition: background-color 0.5s ease;
      }
      
      .box:hover {
          background-color: red;
      }
      ```

    - `all`: 요소의 모든 속성 변경에 대해 전환 애니메이션을 적용

  - **`duration`**: 전환 효과가 지속되는 시간. 예: `2s` (2초), `500ms` (500밀리초)

  - **`timing-function`**: 전환 효과의 가속도 곡선을 정의.

    -  `linear`: 전환 효과가 일정한 속도로 시작되고 끝난다.
    -  `ease`: 전환 효과가 천천히 시작되어 중간에 빠르게 진행되고, 다시 천천히 끝난다.
    -  `ease-in`: 전환 효과가 천천히 시작되어 점점 빨라진다.
    -  `ease-out`: 전환 효과가 빠르게 시작되어 점점 느려진다.
    - `ease-in-out`: 전환 효과가 천천히 시작되어 중간에 빠르게 진행되고, 다시 천천히 끝난다.

  - **`delay`**: 전환 효과가 시작되기 전에 기다리는 시간. 예: `1s` (1초), `200ms` (200밀리초)

  예시

  ```
  .image_upload_popup {
      right: 0;
      position: absolute;
      width: 0;
      height: 0;
      background-color: rgba(0, 0, 0, 0.5);
      z-index: 1000;
      overflow: hidden;
  	transition: width 0.5s 1s ease, height 1s 0.5s ease-in-out;
      color:white;
      display: flex;
      justify-content: center;
  }
  ```

  - width가 변하는 애니메이션은 0.5초 동안 전환되며 지연시간은 1초, ease
  - height가 변하는 애니메이션은 1초 동안 전환되며 지연시간은 0.5초, ease-in-out











#### display: flex, grid 인 경우 

- **justify-content**: Flexbox 또는 CSS Grid 컨테이너의 주 축(main axis)을 따라 자식 요소들을 정렬하는 데 사용된다.

  주 축: 수평 축

  - **`flex-start`**: 자식 요소들을 교차 축의 시작 부분에 정렬한다.
  - **`flex-end`**: 자식 요소들을 교차 축의 끝 부분에 정렬한다.
  - **`center`**: 자식 요소들을 교차 축의 중앙에 정렬한다.
  - **`space-around`**: 자식 요소들 주위에 동일한 간격을 둔다. 요소의 양 끝에도 동일한 간격의 절반을 둔다.
  - **`space-evenly`**: 자식 요소들 사이와 양 끝에 동일한 간격을 둔다.

- **align-items**: Flexbox 또는 CSS Grid 컨테이너의 교차 축(cross axis)을 따라 자식 요소들을 정렬하는 데 사용된다.

  교차 축: 수직 축

  - **`flex-start`**: 자식 요소들을 교차 축의 시작 부분에 정렬한다.

  - **`flex-end`**: 자식 요소들을 교차 축의 끝 부분에 정렬한다.

  - **`center`**: 자식 요소들을 교차 축의 중앙에 정렬한다.

  - **`baseline`**: 자식 요소들의 텍스트 베이스라인을 기준으로 정렬한다.

  - **`stretch`**: 자식 요소들을 교차 축을 따라 늘려서 컨테이너의 크기를 채운다.

    자식 요소의 높이나 너비가 명시되지 않은 경우에만 적용된다.

- **flex-direction**: Flex 항목들이 주 축(main axis)을 따라 배치되는 방향을 설정한다.

  - **`row`**: Flex 항목들이 주 축을 따라 가로 방향(왼쪽에서 오른쪽)으로 배치된다. (default)
  - **`row-reverse`** :Flex 항목들이 주 축을 따라 가로 방향(오른쪽에서 왼쪽)으로 배치된다.
  - **`column`** : Flex 항목들이 주 축을 따라 세로 방향(위에서 아래)으로 배치된다.
  - **`column-reverse`**: Flex 항목들이 주 축을 따라 세로 방향(아래에서 위)으로 배치된다.

- **flex-wrap**: Flex 항목들이 한 줄에 배치될지, 여러 줄로 나뉘어 배치될지를 결정한다.

  - **`nowrap`**: 모든 Flex 항목들이 한 줄에 배치된다. (default)
  - **`wrap`**:Flex 항목들이 여러 줄로 나뉘어 배치된다. 필요에 따라 항목들이 새 줄로 넘어간다.
  - **`wrap-reverse`**: Flex 항목들이 여러 줄로 나뉘어 배치되지만, 역방향으로 배치된다. 새 줄이 위쪽으로 쌓임







## CSS 적용 방법

CSS를 HTML에 적용하는 방법은 세 가지가 있다.

- **인라인 스타일(In-line Style)**:

  - HTML 요소의 `style` 속성에 직접 CSS를 작성합니다.
  - 예: `<p style="color: red;">This is a paragraph.</p>`

- **내부 스타일(Internal Style)**:

  - HTML 문서의 `<head>` 섹션에 `<style>` 태그를 사용하여 CSS를 작성합니다.

  - 예:

    ```
    <head>
        <style>
            p {
                color: red;
            }
        </style>
    </head>
    ```

- **외부 스타일(External Style)**:

  - 별도의 CSS 파일을 작성하고, HTML 문서의 `<head>` 섹션에 `<link>` 태그를 사용하여 연결합니다.

  - 예:

    ```
    <head>
        <link rel="stylesheet" href="styles.css">
    </head>
    ```

    