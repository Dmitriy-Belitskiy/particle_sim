#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np


# In[2]:


data=np.loadtxt("lines.txt")


# In[3]:


map_zero=data[:,2]==0

map_nonne_zero=data[:,2]!=0
map_en_lim=data[:,1]>=20


np.count_nonzero(np.logical_and(map_zero,map_en_lim))

data_v2=data[np.logical_and(map_nonne_zero,map_en_lim)]


# In[4]:


sources=np.unique(data_v2[:,0])

data_per_source=[]
for i in sources:
    source=np.where(data_v2[:,0] == i)
    data_per_source.append(data_v2[source])
    
data_per_source_norm=[]
for i in data_per_source:
    dat_s = np.array(i)
    sum_s = np.sum(dat_s[:,2])
    if sum_s!=0:
        
        dat_s[:,2]=dat_s[:,2]/sum_s
    
    data_per_source_norm.append(dat_s[dat_s[:,2]>0.0001])
    
    
    
#data_per_source_norm=data_per_source_norm[1:3]


# In[5]:


def generate_loop(file,dat):

        file.write(
        """
        /analysis/openFile dump/data_root/output_{}_.root
        /gps/source/clear
        """.format(int(dat[0,0])))
        #write source data
        for number,line,intencity in dat:
            file.write("""       
            /gps/source/add 1
            /gps/pos/type Plane
            /gps/pos/shape Square
            /gps/pos/centre 0 -2 0 m
            /gps/pos/halfx 0.004 m
            /gps/pos/halfy 0.02 m
            /gps/pos/rot1 1 0 0
            /gps/pos/rot2 0 0 -1

            /gps/direction 0 1 0
            /gps/particle gamma
            /gps/ene/type Mono
            /gps/ene/mono {:.3f} MeV
            /gps/source/intensity {:.5f}
            """.format(line/1000,intencity))
        
        
        for i in range(0,92,2):
            file.write("""/B5/detector/setRotX {}
                    /run/initialize
                    /run/beamOn 10000
                    /analysis/write
                    /analysis/reset
                    
                    
        """.format(i))
        
        file.write("/analysis/closeFile")


# In[6]:


def generate_macro_file_head(filename="gen_all_isotops.mac"):
    with open(filename, "w") as f:
        # Write the initial part of the macro
        f.write("""/control/verbose 0
        /run/verbose 0
        /event/verbose 0
        /tracking/verbose 0
        /run/printProgress 1000
        /run/initialize
        /gps/source/clear
        
        /B5/detector/setPositionX 0
        /B5/detector/setPositionY -1
        /B5/detector/setPositionZ 0
        
        
        """)
        for i in data_per_source_norm: 
            f.write("/control/execute scripts/source{}.mac\n".format(int(i[0,0])))
               
    


# In[7]:


generate_macro_file_head()


# In[8]:


for i in data_per_source_norm: 
    
        filename = 'scripts/source{}.mac'.format(int(i[0,0]))
        with open(filename, "w") as f:
            generate_loop(f,i)


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




