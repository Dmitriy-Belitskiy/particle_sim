#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import matplotlib.pyplot as plt


# In[2]:


#base_comands
aX = "/B5/detector/setPositionX {}"
aY = "/B5/detector/setPositionY {}"
aZ = "/B5/detector/setPositionZ {}"
init="/run/initialize" 
run=1000000
shoot="/run/beamOn {}"
progres="/run/printProgress 10000"


# In[3]:


Y=0
X=0


# In[4]:


Z= np.linspace(-4,4,50)


# In[5]:


with open('test.mac', 'w') as f:

    f.write("/control/verbose 0")
    f.write('\n')
    f.write("/run/verbose 0")
    f.write('\n')
    f.write("/event/verbose 0")
    f.write('\n')
    f.write("/tracking/verbose 0")
    f.write('\n')
    f.write(progres)
    f.write('\n')
    for i in Z:
            
            f.write(init)
            f.write('\n')
            f.write(aX.format(X))
            f.write('\n')

            f.write(aY.format(Y))
            f.write('\n')

            f.write(aZ.format(i))
            f.write('\n')

            f.write(shoot.format(run))
            f.write('\n')


# In[ ]:





# In[ ]:





# In[ ]:




