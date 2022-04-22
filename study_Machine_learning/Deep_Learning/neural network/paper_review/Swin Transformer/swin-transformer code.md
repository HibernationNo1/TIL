# swin-transformer







## PatchEmbed

PatchEmbed : Patch Partition + Linear Embedding

image를 patch로 나누고 각 patch를 embedding하는 module이다.



```python
patch_embed = PatchEmbed(
    			img_size=img_size,
    			patch_size=patch_size,
    			in_chans=in_chans,
    			embed_dim=embed_dim,
            	norm_layer=norm_layer if self.patch_norm else None)
```



```python
class PatchEmbed(nn.Module):
    r""" Image to Patch Embedding

    Args:
        img_size (int): Image size.  Default: 224.
        patch_size (int): Patch token size. Default: 4.
        in_chans (int): Number of input image channels. Default: 3.
        embed_dim (int): Number of linear projection output channels. Default: 96.
        norm_layer (nn.Module, optional): Normalization layer. Default: None
    """

    def __init__(self, img_size=224, patch_size=4, in_chans=3, embed_dim=96, norm_layer=None):
        super().__init__()
        print(f"img_size : {img_size},  patch_size : {patch_size}")
        

        img_size = to_2tuple(img_size)
        patch_size = to_2tuple(patch_size)
        patches_resolution = [img_size[0] // patch_size[0], img_size[1] // patch_size[1]]   # patch개수 (N, N)
    
        self.img_size = img_size
        self.patch_size = patch_size
        self.patches_resolution = patches_resolution
        self.num_patches = patches_resolution[0] * patches_resolution[1]                    # patch개수 (N * N)

        self.in_chans = in_chans
        self.embed_dim = embed_dim

        # kernel size와 stride를 모두 patch size 만큼 주기 때문에, patch partition과 embedidng을 동시에 진행할 수 있다.
        # input : [batch_size, channel, width, height],     output : [batch_size, embed_dim, patches_resolution[0], patches_resolution[1]]
        self.proj = nn.Conv2d(in_chans, embed_dim, kernel_size=patch_size, stride=patch_size)

        if norm_layer is not None:
            self.norm = norm_layer(embed_dim)
        else:
            self.norm = None

    def forward(self, x):
        B, C, H, W = x.shape
        # FIXME look at relaxing size constraints
        assert H == self.img_size[0] and W == self.img_size[1], \
            f"Input image size ({H}*{W}) doesn't match model ({self.img_size[0]}*{self.img_size[1]})."
        x = self.proj(x).flatten(2).transpose(1, 2)  # B Ph*Pw C
        if self.norm is not None:
            x = self.norm(x)
        return x

    def flops(self):
        Ho, Wo = self.patches_resolution
        flops = Ho * Wo * self.embed_dim * self.in_chans * (self.patch_size[0] * self.patch_size[1])
        if self.norm is not None:
            flops += Ho * Wo * self.embed_dim
        return flops
```





## BasicLayer



### SwinTransformerBlock

```python
```



#### WindowAttention

window단위로 self attention을 계산