import numpy as np
import matplotlib.pyplot as plt

def compute_chi(rhos,volumes, axis=0,stride=1,verbose=False):
    if verbose: print("The number of indeendent samples is", volumes[::stride].shape[0])
    avg_v = volumes[::stride].mean()
    avg_rho = rhos[::stride].mean(axis=axis)
    avg_rho_v = np.mean(volumes[::stride,np.newaxis]*rhos[::stride], axis=axis)
    return -(avg_rho_v-avg_v*avg_rho)


class ChiAnalyser:
    def __init__(self, folder,nbins=60):
        self.folder = folder
        print(f"::: Analysing folder {folder}...")
        _r,_rho = np.loadtxt(f"{folder}/profiles.txt", unpack = True)
        self.csv = np.loadtxt(f"{folder}/output.csv",skiprows=1,delimiter=',')

        self.rhos = _rho.reshape((-1, nbins))
        self.rs = _r.reshape((-1, nbins)).mean(axis=0)
        assert self.rhos.shape[0] == self.csv.shape[0],f"CSV and profiles.txt files do not match, {self.ns.shape[0]}{self.csv.shape[0]}"
        self.volumes = self.csv[:,-1]
        self.compute_chi()

    def compute_chi(self):
        """Calculate the compressibility chi from the cross-covariance """
        self.chi = compute_chi(self.rhos,self.volumes)

    def plot(self,ax=None):
        if ax==None:
            fig,ax = plt.subplots()
        
        self.line,  = ax.plot(self.rs,self.chi)

