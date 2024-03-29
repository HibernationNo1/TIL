# License

|      |                                                | MIT  | Apache | MPL  | EPL    | LGPL2       | GPL2        | GPL3        | AGPL3       |
| ---- | ---------------------------------------------- | ---- | ------ | ---- | ------ | ----------- | ----------- | ----------- | ----------- |
| 1    | 수정, 배포의 권한허용                          | O    | O      | O    | O      | O           | O           | O           | O           |
| 2    | 배포 시 라이선스 사본 첨부                     | O    | O      | O    | O      | O           | O           | O           | O           |
| 3    | 저작권 고지사항 또는 Attribution 고지사항 유지 | O    | O      | O    | O      | O           | O           | O           | O           |
| 4    | ★ 배포시 소스코드 제공의무와 범위              |      |        | File | Module | 파생 저작물 | 파생 저작물 | 파생 저작물 | 파생 저작물 |
| 5    | 동일 라이선스로만 배포                         |      |        | O    | O      | O           | O           | O           | O           |
| 6    | 수정시 수정내용 고지                           |      | O      | O    | O      | O           | O           | O           | O           |
| 7    | 명시적 특허 라이선스의 허용                    |      | O      | O    | O      |             |             | O           | O           |
| 8    | 특허소송 제기 시 라이선스 종료                 |      | O      | O    | O      |             |             | O           | O           |



- **수정, 배포의 권한허용** :  수정과 배포가 가능하다.

- 배포시 라이선스 사본 첨부 : 배포 시 꼭 원작자의 라이선스 사본을 첨부해야 한다.

- **저작권 고지사항 또는 Attribution 고지사항 유지** : 코드의 상단에 삽입되어 있는 원작자의 저작권고지사항을 지우면 않되고 그대로 유지를 해야 한다.

- **★ 배포 시 소스코드 제공의무와 범위** : 해당 오픈소스를 사용하여 개발할 경우 개발된 소스코드도 사용자에게 제공해야할 의무가 있다. (Open source) 

  > 기업체에서 사용시 많은 주의가 필요한 항목입니다.

- **동일 라이선스로만 배포** : 원작자가 지정한 라이선를 바꿀수 없음을 의미

- **수정시 수정내용 고지** : 오픈소스를 수정한 경우 수정사항에 대해 고지를 해야 한다.

- **명시적 특허 라이선스의 허용**

- **특허소송 제기 시 라이선스 종료**



---

- Apache, MIT, BSD :  사용 시 소스공개에 대한 위험성이 없으므로 비교적 자유롭게 사용이 가능한 라이선스

- MPL, EPL, LGPL, GPL : 사용시 꼼꼼히 확인하고 주의를 해야 하는 라이선스

  > e.g. 
  >
  > GPL : `수정` `배포`의 범위가 원작자가 배포한 배포본의 패키지에 한정되어 있으며 해당 오픈소스를 사용한 경우 개발한 프로그램의 소스도 공개해야 한다.

- AGPL : `수정` `배포`의 범위가 패키지에만 한정된 것이 아니고 온라인으로 서비스하는 것 까지 배포로 정의한다.

  > e.g. 
  >
  > **AGPL**의 라이선스를 가진 오픈소스로 웹사이트를 개발하여 서비스를 한다면 그 자체로 라이선스 위반.

---



### 오픈소스를 사용할 때 주의할 사항

1. 특허 침해

   오픈소스 라이센스는 사용철회 조항에 특허 침해에 관한 것을 다루고 있으며, 잘 이해해야 하며, 영리적인 목적을 추구할 때에는 특히, 사용한 오픈소스에 의해서 특허침해가 있을지 없을지 고민해봐야 한다.



#### Apache

**아파치 라이센스 2.0**

- open source를 통해 영리적인 목적(비지니스 등)을 달성해도 문제 없다.

- 2차 제작물의 소스코드 공개의무가 없음

- **LICENSE** md파일을 만들어 Apache License 2.0 전문(영문)을 포함해야 한다.

  > 최상단 디렉터리에 위치

- NOTICES md 파일을 만들어 수정된 파일에 대해 수정사항을 표시한 안내문구를 적어놓아야 한다.

- 내가 진행한 2차 제작물에 자체적으로 저작권 표시를 추가할 수 있으며, 

  2차 제작물의 사용, 복제, 배포, 혹은 그러한 파생 저작물 전체에 대해 추가적인 라이선스 조항이나 별도의 라이선스 조항들을 만들 수 있다. 

  >  단, 이는 저작물에 대한 당신의 사용, 복제 및 배포 행위가 그 외의 사항들에서는 본 라이선스에 명시된 조건들을 준수한다는 것을 전제로 한다.

- 라이센서의 상호나 상표, 서비스 표, 제품명을 사용하면 안된다.(있으면 전부 지워야함)



> github의 detectron2의 [LICENSE](https://github.com/facebookresearch/detectron2/blob/main/LICENSE) 파일 참고
>
> 티스토리 [설명](https://erim1005.tistory.com/entry/Apache-License-20-%EC%98%A4%ED%94%88%EC%86%8C%EC%8A%A4SW-%EB%9D%BC%EC%9D%B4%EC%84%A0%EC%8A%A4) 참고