import matplotlib.pyplot as plt
from scipy.fftpack import fft, ifft
from scipy.signal import fftconvolve
from scipy.io import wavfile # get the api
import numpy as np
import soundfile as sf

def clamp(n, smallest, largest): 
    return max(smallest, min(n, largest))

def fft_mono(data, channel, bitDepth=24, maxSamples=None):
    '''
    Performs FFT on single channel. Assumes input data is stereo.
    '''
    F = data.T[channel]         # Get out single channel
    if maxSamples != None:
        F = F[:maxSamples]
    G = [(x/2**bitDepth) for x in F]  # Normalize into -1,1 range
    G_fft = fft(G)              # Do fft
    return G_fft

def get_real(data):
    N = len(data)//2               
    out = abs(data[:(N-1)])   # Get first half (symmetry) real part.
    return out


def main():
    """ fs, file = wavfile.read('./input/tube_mp_impulse_res.wav') # load the data
    data = fft_mono(file, 0)

    fs2, file2 = wavfile.read('./input/clean_git.wav') # load the data
    data2= fft_mono(file2, 0, maxSamples=44100)
    print(len(file), len(file2)) """

    """ conv = ifft(data * data2).astype(np.int32)
    conv = conv / np.iinfo(np.int32).max """
    """ conv = fftconvolve(file, file2)
    wavfile.write('out.wav', fs, file2) """
    
    #print(max(conv))
    """ plt.plot(conv, 'r')
    plt.plot(file2, 'b')
    
    plt.show() """

    data, sr = sf.read('./input/clean_git.wav')
    left = [i[0] for i in data]
    right = [i[1] for i in data]

    ir, sr2 = sf.read('./input/tube_mp_impulse_res.wav')
    ir_left = [i[0]*50 for i in ir]
    ir_right = [i[1]*50 for i in ir]

    conv_left = fftconvolve(ir_left, left)
    conv_right = fftconvolve(ir_right, right)

    outData = []
    for x in range(len(conv_left)):
        outData.append([conv_left[x], conv_right[x]])

    sf.write('out.wav', outData, sr)

    plt.plot(ir)
    plt.show()

if __name__ == '__main__':
    main()