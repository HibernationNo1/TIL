# Git LFS

Github의 경우 50Mb부터 Warning이 표시되고, 100Mb부터는 push시 Error가 발생한다. 그럼에도 불구하고 경우에 따라서 반드시 대용량 파일을 git repo에 포함시켜야하는 상황에서 사용하는 것이 Git LFS이다.



### install

https://git-lfs.github.com/ 

또는

```
$ curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | sudo bash
$ sudo apt install git-lfs
```



### LFS로 File 관리하기

1. **특정 repo에 git lfs 적용하기**

   ```
   $ git lfs install
   ```

   .gitattributes file이 생성된다.

2. **lfs로 관리할 file을 track에 등록** 

   ```
   $ git lfs track <file path>
   ```

   해당 파일의 내용이 원래의 contents가 아니라, lfs pointer로 바뀌는 것을 알 수 있다.

   > 만약 기존에 add해둔 파일을 lfs로 관리해야하는 상황이라면 git rm --cache로 먼저 unstaging을 시킨 다음, 다시 git lfs track을 해야한다.
   >
   > ```
   > git rm --cahced <file path>
   > git lfs track <file path>
   > ```

   

   
   
3. **add, commit .gitattributes**

   ```
   git add .gitattributes
   git commit -m "update gitattributes for lfs"
   ```

   lfs로 트래킹하는 파일에 대한 정보는 .gitattributes을 통해서 관리가 되어 이 변경사항을 꼭 add해주어야한다. 

   이후 해당 file의 push는 일반적인 git push와 동일하다.



`.gitattributes`의 맨 마지막 라인을 보면 어떤 규칙으로 파일들이 lfs로 관리되고 있는지 볼 수 있다.



### LFS File 관리 해제하기

1. **untrack file**

   ```
   $ git lfs untrack <file>
   ```

   > (또는 .gitattributes에서 수동으로 삭제)

2. **lfs file unstaging**

   untrack을 하더라도 .gitattributes의 내용만 변경되고, 실제로 해당 file의 내용은 아직도 lfs pointer인 상태로 유지되고 있다

   따라서 `rm --cache`를 이용해서 unstaging를 해준다.

   ```
   $ git rm --cached <file>
   ```

3. **add**

   unstaging한 후 다시 add해주어야, git lfs 가 관리하던 파일에서, 다시 일반적인 git이 관리하는 파일로 변경된다.

   ```
   $ git add <file>
   ```

   



### 기타 명령어

- lfs로 관리중인 file 목록 확인

  ```
  $ git lfs ls-files
  ```

  

- **LFS가 적용된 repo clone하기**

  git clone을 하고나서 pull이나 fetch를 해도 제대로 lfs가 동작하지 않고, pointer정보만 가져오게 되므로, 이 때는 git lfs pull을 해주어야한다.

  ```
  $ git clone [url]
  $ git lfs pull
  ```

  

