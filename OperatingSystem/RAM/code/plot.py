import matplotlib.pyplot as plt
import math


def Plot_forktimes(f, nbytes, path):
    lines = f.readlines()
    line_s = [line.split() for line in lines]

    forktimes = [float(line[-1]) for line in line_s]
    latency = [float(line[9]) for line in line_s]
    thoughout = [float(line[6]) for line in line_s]

    fig = plt.figure()
    ax1 = fig.add_subplot(111)
    ax1.set_title("block size: " + str(nbytes) + " bytes")
    lns1 = ax1.plot(forktimes, thoughout, 'r', label="thoughout")
    ax1.set_ylabel("thoughout (Mb/s)")
    ax1.set_xlabel("forktimes")
    # ax1.set_ylim(bottom = 0, top = 300)

    ax2 = ax1.twinx()
    lns2 = ax2.plot(forktimes, latency, 'b', label="lantency")
    ax2.set_ylabel("lantency (ms)")
    # ax2.set_ylim(bottom = 0, top = 300)

    lns = lns1+lns2
    labs = [l.get_label() for l in lns]
    ax1.legend(lns, labs, loc=0)

    plt.savefig(path + str(nbytes) + "_b.jpg")


def Read_Write(f_disc_ran, f_disc_seq, f_ram_ran, f_ram_seq, path):
    nbytes, dr = select(f_disc_ran)
    nbytes, ds = select(f_disc_seq)
    nbytes, rr = select(f_ram_ran)
    nbytes, rs = select(f_ram_seq)

    fig = plt.figure()
    ax = fig.add_subplot(111)
    # ax.plot(nbytes, dr, 'r', label="read_disc_ran", marker= 'o')
    # ax.plot(nbytes, ds, 'r', label="read_disc_seq", marker = 'D')
    # ax.plot(nbytes, rr, 'b', label="read_ram_ran", marker= 'o')
    # ax.plot(nbytes, rs, 'b', label="read_ram_seq", marker = 'D')
    ax.plot(nbytes, dr, 'r', label="write_disc_ran", marker= 'o')
    ax.plot(nbytes, ds, 'r', label="write_disc_seq", marker = 'D')
    ax.plot(nbytes, rr, 'b', label="write_ram_ran", marker= 'o')
    ax.plot(nbytes, rs, 'b', label="write_ram_seq", marker = 'D')
    ax.set_ylabel("thoughout (Mb/s)")
    ax.set_xlabel("nbytes (byte)")

    handles, labels = ax.get_legend_handles_labels()
    ax.legend(handles[::-1], labels[::-1])

    # plt.savefig(path + "read.jpg")
    plt.savefig(path + "write.jpg")

def Ram_disc(f_write_disc, f_write_ram, f_read_disc, f_read_ram, path):
    nbytes, wd = select(f_write_disc)
    nbytes, wr = select(f_write_ram)
    nbytes, rd = select(f_read_disc)
    nbytes, rr = select(f_read_ram)

    fig = plt.figure()
    ax = fig.add_subplot(111)
    # ax.plot(nbytes, wd, 'r', label="write_disc_seq", marker= 'o')
    # ax.plot(nbytes, wr, 'r', label="write_ram_seq", marker = 'D')
    # ax.plot(nbytes, rd, 'b', label="read_disc_seq", marker= 'o')
    # ax.plot(nbytes, rr, 'b', label="read_ram_seq", marker = 'D')
    ax.plot(nbytes, wd, 'r', label="write_disc_ran", marker= 'o')
    ax.plot(nbytes, wr, 'r', label="write_ram_ran", marker = 'D')
    ax.plot(nbytes, rd, 'b', label="read_disc_ran", marker= 'o')
    ax.plot(nbytes, rr, 'b', label="read_ram_ran", marker = 'D')

    ax.set_ylabel("thoughout (Mb/s)")
    ax.set_xlabel("nbytes (byte)")

    handles, labels = ax.get_legend_handles_labels()
    ax.legend(handles[::-1], labels[::-1])

    plt.savefig(path + "ramdom.jpg")
    # plt.savefig(path + "sequential.jpg")




def select(f):
    lines = f.readlines()
    line_s = [line.split() for line in lines]

    nbytes = []
    thoughout = []

    for line in line_s:
        nbytes.append(int(line[3]))
        thoughout.append(float(line[6]))
    return (nbytes, thoughout)





path = "E:\\school\\2-2\\os\\minix_code\\project3\\code\\data\\"
# wdr = open(path+"wdr.txt", "r")
# wds = open(path+"wds.txt", "r")
# wrr = open(path+"wrr.txt", "r")
# wrs = open(path+"wrs.txt", "r")
# Read_Write(wdr, wds, wrr, wrs, path)
# rdr = open(path+"rdr.txt", "r")
# rds = open(path+"rds.txt", "r")
# rrr = open(path+"rrr.txt", "r")
# rrs = open(path+"rrs.txt", "r")
# Read_Write(rdr, rds, rrr, rrs, path)
wd = open(path+"wdr.txt", "r")
wr = open(path+"wrr.txt", "r")
rd = open(path+"rdr.txt", "r")
rr = open(path+"rrr.txt", "r")
Ram_disc(wd, wr, rd, rr, path)
# wd = open(path+"wds.txt", "r")
# wr = open(path+"wrs.txt", "r")
# rd = open(path+"rds.txt", "r")
# rr = open(path+"rrs.txt", "r")
# Ram_disc(wd, wr, rd, rr, path)



# path = "E:\\school\\2-2\\os\\minix_code\\project3\\code\\data\\r_r_s\\"
# for i in range(6, 13):
#     nbytes = pow(2,i)
#     f_name = path + "r_r_s_" + str(nbytes) + "b.txt"
#     f = open(f_name, "r")
#     Plot_forktimes(f, nbytes, path)
#     f.close()

