# Line Plot

Line plot shows by connecting serveral point with a line



#### 1. ax.plot(y)

전달인자가 1개인 plot

push only one argument in plot

```python
y_data = np.random.normal(loc=0, scale = 1, size = (300, ))

fig, ax =plt.subplots(figsize = (10, 5))
ax.plot(y_data)
```

> x axis express index of y_data



ex)

```python
y_data = np.random.normal(loc=0, scale = 1, size = (300, ))

fig, ax =plt.subplots(figsize = (10, 5))
ax.plot(y_data)

ax.grid()

for spine_loc, spine in ax.spines.items():
    spine.set_linewidth(2)
    if spine_loc in ['right', 'top']:
        spine.set_visible(False)

    if spine_loc in ['bottom', 'left']:
        spine.set_position(('data', 0))

plt.show()
```



#### 2. ax.plot(x, y)

전달인자가 2개인 plot

push two argument in plot

ex)

```python
n_data = 100
s_idx = 30

x_data = np.arange(s_idx, s_idx + n_data)
y_data = np.random.normal(0, 1, size = (n_data, ))

fig, ax = plt.subplots(figsize = (10, 5))
ax.plot(x_data, y_data)

fig.tight_layout(pad = 3)
x_ticks = np.arange(s_idx, s_idx + n_data + 1, 20)
ax.set_xticks(x_ticks)

ax.tick_params(labelsize = 15)

plt.show()
```

