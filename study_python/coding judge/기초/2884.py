h, m = map(int, input().split())

m_ff = m - 45

if m_ff >= 0:
    aft_m = m_ff
    aft_h = h
else:
    aft_m = 60 - (abs(m_ff) % 60)  
    aft_h = h - 1 - abs(m_ff)//60
    
    if aft_h < 0:
        aft_h = 24 - (abs(aft_h) % 24)

print(aft_h, aft_m)