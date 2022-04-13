# apex

pytorch를 사용해 model을 최적화 시키고 batch size를 늘리는 방법으로, NVIDIA에서 만든 **'A Pytorch EXtension'(APEX)** 이라는 package이다. 

https://github.com/NVIDIA/apex				한글 설명 : https://cvml.tistory.com/8

APEX 패키지에는 mixed precision training과 distributed training 기능이 있다.



installation은 위 링크에서 확인

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
   if config.AMP_OPT_LEVEL != "O0":	# 이 때 opt_level = "01" 이도록 한다.
   	model, optimizer = amp.initialize(model, optimizer, opt_level=config.AMP_OPT_LEVEL)
   ```

   > `build_model`와 `build_optimizer` 는 custum funtion

2. 학습 중에 with문을 통해 loss와 optimizer를  amp.scale_loss로 호출한 후  scaled_loss으로 명명한다.

   이후 scaled_loss를 통해 back propagation을 진행한다.

   ```python
   with amp.scale_loss(loss, optimizer) as scaled_loss:
       scaled_loss.backward()
   ```

   

   







#### distributed training