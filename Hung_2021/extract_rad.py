import pandas as pd

df_dat = pd.read_csv('radTable.dat', sep=" ")

df_ccdc = df_dat[["Element", "RCCDC-vdW"]]
df_ccdc.to_csv('rad_ccdc.rad', header=False, index=False, sep=" ")

df_uff = df_dat[["Element", "Rt-r-vdW_300K"]]
df_uff.dropna(inplace=True)
df_uff.to_csv('rad_uff_300k.rad', header=False, index=False, sep=" ")
