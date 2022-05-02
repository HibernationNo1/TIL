# apex

pytorch를 사용해 model을 최적화 시키고 batch size를 늘리는 방법으로, NVIDIA에서 만든 **'A Pytorch EXtension'(APEX)** 이라는 package이다. 

https://github.com/NVIDIA/apex				한글 설명 : https://cvml.tistory.com/8

APEX 패키지에는 mixed precision training과 distributed training 기능이 있다.



installation은 위 링크에서 확인

또는

```
$ git clone https://github.com/NVIDIA/apex
$ cd apex
$ python setup.py install --cuda_ext --cpp_ext
```

> - error
>
>   ```
>   Microsoft Visual C++ 14.0 or greater is required. Get it with "Microsoft C++ Build Tools": https://visualstudio.microsoft.com/visual-cpp-build-tools/
>   ```
>
>   https://visualstudio.microsoft.com/visual-cpp-build-tools/ 에서 tool 다운받아야 함
>
>   
>
> 
>
> cuda toolkit 10.2 에서 됨을 확인 (그 이상 version에서 issue발생)
>
> 







code초반부에 아래 문구를 넣어서 apex사용이 가능한지 확인할 것.

```python
try:
    # noinspection PyUnresolvedReferences
    from apex import amp
except ImportError:
    amp = None


assert amp is not None, "amp not installed!"
```





#### mixed precision training

- 처리 속도를 높이기 위한 FP16(16bit floating point)연산과 정확도 유지를 위한 FP32 연산을 섞어 학습하는 방법이다.

- Tensor Core를 활용한 FP16연산을 이용하면 FP32연산 대비 절반의 메모리 사용량과 8배의 연산 처리량 & 2배의 메모리 처리량 효과가 있다

  > 최적화가 되어 배치를 늘릴 수 있기 때문에 학습 속도가 빨라지지만 배치 뿐만 아니라 모델 최적화도 이루어지기 때문에 속도가 증가한다.

- 최적의 사용 조건

  > Tensor Core를 이용하여 FP16 연산이 가능한 Volta 이상의 NVIDIA 그래픽 카드 (V100, RTX2080ti, ...)



**사용 방법**

1. model과 optimaizer를 인자로 삼아 `amp.initialize`를 호출한다.

   ```python
   # model과 optimizer를 build한다.
   model = build_model(config)
   optimizer = build_optimizer(config, model)
   
   # build한 model과 optimizer를 argument로 삼아 amp.initialize를 호출한다.
   if AMP_OPT_LEVEL != "O0":	
   	model, optimizer = amp.initialize(model, optimizer, opt_level=config.AMP_OPT_LEVEL)
   ```

   > - AMP_OPT_LEVEL :
   >
   >   `O0`: apex를 사용하지 않는 경우
   >
   >   `O1`, `O2`: apex를 제대로 사용하기 위한 정밀도 lavel로, 둘 다 시도한 후 model에 가장 적합한 값을 사용한다.
   >
   >    `O3` : 제대로된 구현을 사용하진 않게 되지만, 속도 기준선을 설정하는데 유용하다. (보통 사용 안함) 
   >
   > - `build_model`와 `build_optimizer` 는 custum funtion
   >
   > ```
   > # 출력
   > Selected optimization level O1:  Insert automatic casts around Pytorch functions and Tensor methods.
   > 
   > Defaults for this optimization level are:
   > enabled                : True
   > opt_level              : O1
   > cast_model_type        : None
   > patch_torch_functions  : True
   > keep_batchnorm_fp32    : None
   > master_weights         : None
   > loss_scale             : dynamic
   > Processing user overrides (additional kwargs that are not None)...
   > After processing overrides, optimization options are:
   > enabled                : True
   > opt_level              : O1
   > cast_model_type        : None
   > patch_torch_functions  : True
   > keep_batchnorm_fp32    : None
   > master_weights         : None
   > loss_scale             : dynamic
   > ```
   >
   > - warning 발생시
   >
   >   ```
   >   Warning:  multi_tensor_applier fused unscale kernel is unavailable, possibly because apex was installed without --cuda_ext --cpp_ext. Using Python fallback.  Original ImportError was: ModuleNotFoundError("No module named 'amp_C'")
   >   ```
   >
   >   

2. 학습 중에 with문을 통해 loss와 optimizer를  amp.scale_loss로 호출한 후  scaled_loss으로 명명한다.

   이후 scaled_loss를 통해 back propagation을 진행한다.

   ```python
   with amp.scale_loss(loss, optimizer) as scaled_loss:
       scaled_loss.backward()
   ```

   

   







#### distributed training