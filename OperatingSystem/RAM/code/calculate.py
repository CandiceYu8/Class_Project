import math      

def Seperate(f_read, f_write_name):
    """ to seperate by nbytes to different files """
    lines = f_read.readlines()
    line_s = [line.split() for line in lines]

    for i in range(6, 13):
        nbytes = pow(2,i)
        f_write = f_write_name + str(nbytes) + "b.txt"
        f = open(f_write, "w+")

        for line in line_s:
            if line[3] == str(nbytes):
                f.write(" ".join(line))
                f.write("\n")
        f.close()


f1 = open("E:\\school\\2-2\\os\\minix_code\\project3\\code\\data\\r_r_s\\r_r_s.txt", "r")
f2_name = "E:\\school\\2-2\\os\\minix_code\\project3\\code\\data\\r_r_s\\r_r_s_"
Seperate(f1, f2_name)
f1.close()
