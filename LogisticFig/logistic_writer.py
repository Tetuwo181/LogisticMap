# -*- coding: utf-8 -*-

from . import logistic_interface as LI
import os
import sys
from datetime import datetime


def execute(init_x:float = 0.1,
        record_num:int = 500,
        iterate_num:int = 5000,
        a_interval:float = 0.005,
        a_min:float = 2.5,
        file_name:str= datetime.now().strftime("%Y_%m_%d_%H_%M_%S") + ".png"):
    fig_dir = os.path.join(os.getcwd(), "graph")
    if os.path.exists(fig_dir) is False:
        os.mkdir(fig_dir)
    df = LI.run(init_x, record_num, iterate_num, a_interval, a_min)
    graph = df.plot.scatter(x="a", y = "limit", s = 0.0001)
    fig = graph.get_figure()
    fig.savefig(os.path.join(fig_dir, file_name))

def main(args):
    if len(args) == 1:
        return main()
    if len(args) == 2:
        return main(float(args[1]))
    if len(args) == 3:
        return main(float(args[1]), int(args[2]))
    if len(args) == 4:
        return main(float(args[1]), int(args[2]), int(args[3]))
    if len(args) == 5:
        return main(float(args[1]), int(args[2]), int(args[3]), float(args[4]))        
    if len(args) == 6:
        return main(float(args[1]), int(args[2]), int(args[3]), float(args[4]), float(args[5]))
    if len(args) == 7:
        return main(float(args[1]), int(args[2]), int(args[3]), float(args[4]), float(args[5]), args[6])        


main(sys.argv)