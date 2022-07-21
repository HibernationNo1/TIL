# compiler

pipeline을 compile할때 사용

```python
import kfp.compiler as compiler
```



#### Compiler()

```python
compiler.Compiler(mode = 
				  ).compile(pipeline_func = ,
                            package_path = )
```

- `mode` 

  - `kfp.dsl.PipelineExecutionMode.V2_COMPATIBLE` : 

    `client.create_run_from_pipeline_func` 으로 pipeline을 구성할 경우 사용

  - `kfp.dsl.PipelineExecutionMode.V2_ENGINGE` : 

- `pipeline_func` : compile할 `@dsl.pipeline` 으로 decorator된 pipeline function

- `package_path` : pipeline package를 저장할 path (.yaml format으로 하자)

  `pipeline.yaml`

