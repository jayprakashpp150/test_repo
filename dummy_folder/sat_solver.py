global assigned_value
global sat
global clause
global var_assignment
global final_assignment
global var_count
global clause_count
global li_list
global li_count_list
global li_priority_list
global lit_assigned


def solve(clause_no):
    global final_assignment
    global var_assignment
    global sat
    if clause_no == clause_count:
        final_assignment=var_assignment
        sat=True
        print(clause_no)
        return
    else:
        for i in clause[clause_no]:
            #print(i)
            neg=1
            k=i>>1
            
            if i&1 == 1:
                neg=-1
                k=(i>>1)
            """if clause_no==3:
                print(clause[clause_no])
                print("k = ", k)
                print("neg = ", neg )
                print("ass = ",var_assignment[k-1])
                
            if k==3:
                print("k = ",k," clause no = ",clause_no)
                print("ass ", var_assignment[k-1])
                print("neg = ",neg)"""
            if (var_assignment[k-1]==0) or (neg==var_assignment[k-1]):
                if var_assignment[k-1]==0:
                    var_assignment[k-1]=neg
                """"if clause_no==3:
                    print("assigned = ",var_assignment[k-1])"""
                solve(clause_no+1)
                if sat:
                    break
                #var_assignment[k-1]=0

def print_output():
    print("Result")
    #print(final_assignment)
    #print(var_assignment)
    if sat:
        print("SAT")
        ans_str = "state : "
        t=1
        for i in range(var_count):
            if final_assignment[i] == 'T':
                ans_str+=str(t)+" "
            elif final_assignment[i] == 'F':
                ans_str+=str(-t)+" "
            else:
                ans_str+=str(t)+" "
            t+=1
        print(ans_str)
    else:
        print("UNSAT")




def readInput(file_name):
    infile=open(file_name)
    ls=infile.readlines()
    infile.close()
    flag=False
    global var_count
    global clause_count
    global clause
    global li_list
    global li_count_list
    global li_priority_list
    ct=0
    for i in ls:
        if flag:
            c1=[]
            sp=i.split(' ')
            
            for k in sp[:-1]:
                if k=='0' or k=='0\n':
                    break
                if k=='' or k==' ' or k=='  ' or k=='\t':
                    continue
                if int(k) in c1:
                    continue
                if int(k)<0:
                    t=int(k)
                    li_list[abs(int(k))-1][1].append(ct)
                else:
                    t=int(k)
                    li_list[int(k)-1][0].append(ct)
                c1.append(t)

            """if c1 in clause:
                continue"""    
            clause.append(c1)
            ct+=1
            
        if i[0]=='p':
            sp=i.split(' ')
            var_count=int(sp[2])
            clause_count=int(sp[3])
            li_list=[[[] for in1 in range(2)] for in2 in range(var_count)]
            #print(li_list)
            flag=True
    print("clause count = ",clause_count,"\nvar count = ",var_count,"\n")
    #print(clause)
    
    #computing the count of a positive/negative literal in clauses for following calculation
                    #pure literal finding
                    #prioritize the variable based on their count so to make choice while assigning T/F
    li_count_list=[[0,0] for in1 in range(var_count)]
    li_priority_list=[[0,in1] for in1 in range(var_count)]
    for in1 in range(var_count):
        p=len(li_list[in1][0])
        n=len(li_list[in1][1])
        
        li_priority_list[in1][0]=(1024*p*n)+p+n
        
        
        li_count_list[in1][0]=p
        li_count_list[in1][1]=n
    


def init1():
    global clause
    global var_count
    global clause_count
    clause_count=0
    clause=[]
    var_count=0


def initialize():
    global var_assignment
    global final_assignment
    global sat
    global clause
    global assigned_value
    global lit_assigned
    var_assignment=[]
    for i in range(0,var_count):
        var_assignment.append(0)
    
    final_assignment=[]
    lit_assigned=0
    sat=False
    assigned_value=[]
    



def unit_propagation(clause_var_track,clause_no_track,lit_stack,lit_track,li_count_list,li_list,lit_assigned):
   

    #clause_track1=clause_track.copy()
    assign=[]
    if len(lit_stack)!=0:
        temp=lit_stack.pop()
        lit_assigned+=1
        lit_stack.append(temp)
        assign.append(temp)

    cont=True
    while cont:
        
        for i in clause_no_track:
            length=0
            for j in clause_var_track[i]:       #we can optimize here by moving index computing inside if length==1
                if j==1:
                    length+=1
                if length>1:
                    break
            
            if length==1:
                lit_index1=0
                for j in clause_var_track[i]:
                    if j==1:
                        break
                    lit_index1+=1

                temp_lit=clause[i][lit_index1]       #length zero doesn't mean that it will be at index 0 
                if abs(temp_lit) in assign:
                    continue
                neg='T'
                index=0
                if temp_lit<0:
                    neg='F'
                    index=1
                lit_track[abs(temp_lit)-1]=neg
                

                assign.append(temp_lit)
                #li_count_list[abs(clause_track[i][0])][index]-=1
                #clause_track.remove(clause_track[i])
                lit_assigned+=1
        
        if len(assign)==0:
            cont=False
            continue
        
        for i in assign:
            index=0
            if i<0:
                index=1
            for j in li_list[abs(i)-1][index]:
                clause_no_track.remove(j)
                lit_index=-1
                for k in clause_var_track[j]:
                    lit_index+=1
                    if k==0:
                        continue
                    temp_lit=clause[j][lit_index]
                    index1=0
                    if temp_lit<0:
                        index1=1
                    li_count_list[abs(temp_lit)-1][index1]-=1
                    clause_var_track[j][lit_index]=0
                    if temp_lit==i:
                        continue
                    li_list[abs(temp_lit)-1][index1].remove(j)

                #clause_track.remove(clause_track1[j])
                #debug here
            
            for k in li_list[abs(i)-1][1-index]:
                flag_li=False
                lit_index=-1
                for j in clause_var_track[k]:
                    lit_index+=1
                    if j==0:
                        continue
                    temp_lit=clause[k][lit_index]
                    if i==(-temp_lit):
                        continue
                    if lit_track[abs(temp_lit)-1]=='none' or lit_track[abs(temp_lit)-1]==('F' if temp_lit<0 else 'T'):
                        flag_li=True
                        break
                if not flag_li:
                    return lit_assigned,False 
                
                temp=clause[k].index(-i)
                clause_var_track[k][temp]=0
                li_count_list[abs(i)-1][1-index]-=1

            li_list[abs(i)-1][0]=[]
            li_list[abs(i)-1][1]=[]
            #clause_track1=clause_track.copy()
        assign=[]



    return lit_assigned,True 


def pure_literal(clause_var_track,clause_no_track,lit_track,li_count_list,li_list,lit_assigned):
    
    flag=True
    while flag:
        in1=1
        for i in li_count_list:
            flag=False
            lit=0
            if lit_track[in1-1]=='none':
                if i[0]==0:
                    lit_track[in1-1]='F'
                    lit=(-in1)
                    flag=True
                elif i[1]==0:
                    lit_track[in1-1]='T'
                    lit=in1
                    flag=True

            if flag:
                lit_assigned+=1
                index=0
                if lit<0:
                    index=1
                for j in li_list[abs(lit)-1][index]:
                    clause_no_track.remove(j)
                    lit_index=-1
                    for k in clause_var_track[j]:
                        lit_index+=1
                        if k==0:
                            continue
                        index1=0
                        temp_lit=clause[j][lit_index]
                        if temp_lit<0:
                            index1=1
                        li_count_list[abs(temp_lit)-1][index1]-=1
                        clause_var_track[j][lit_index]=0
                        if temp_lit==lit:
                            continue
                        li_list[abs(temp_lit)-1][index1].remove(j)
                    #clause_track.remove(clause_track[j])
                li_list[abs(lit)-1][0]=[]
                li_list[abs(lit)-1][1]=[]
                li_count_list[abs(lit)-1][index]=0
            in1+=1
    return lit_assigned

def check_consistency(clause_var_track):

    for i in clause_var_track:
        for j in i:
            if j==1:
                return False
    return True

def dpll(clause_var_track,clause_no_track,lit_stack,lit_track,li_count_list,li_list,lit_assigned,li_priority_list):
    global sat
    global final_assignment
    if lit_assigned==var_count:
        sat=True
        final_assignment=lit_track.copy()
        return
    lit_assigned,flag=unit_propagation(clause_var_track,clause_no_track,lit_stack,lit_track,li_count_list,li_list,lit_assigned)
    #return the lit_assigned
    if not flag:
        return
    
    lit_assigned=pure_literal(clause_var_track,clause_no_track,lit_track,li_count_list,li_list,lit_assigned)

    if check_consistency(clause_var_track[:]):
        sat=True
        final_assignment=lit_track.copy()
        return

    while True:     #temp[]
        temp=li_priority_list.pop()
        if lit_track[temp[1]]=='none':
            break
    lit_stack.append(temp[1]+1)
    
    lit_track[temp[1]]='T'
    dpll(deepcopy(clause_var_track),deepcopy(clause_no_track),lit_stack,deepcopy(lit_track),deepcopy(li_count_list),deepcopy(li_list),deepcopy(lit_assigned),deepcopy(li_priority_list))
    if sat:
        return
    lit_stack.pop()

    lit_track[temp[1]]='F'
    lit_stack.append(-(temp[1]+1))
    dpll(deepcopy(clause_var_track),deepcopy(clause_no_track),lit_stack,deepcopy(lit_track),deepcopy(li_count_list),deepcopy(li_list),deepcopy(lit_assigned),deepcopy(li_priority_list))
    lit_track[temp[1]]='none'
    lit_stack.pop()
    li_priority_list.append(temp)







def main(argv):
    print(len(argv))
    a=argv[1]
    print(a)
    """a,b,c=argv
    print("hello ",a)
    print("by ", b)
    print("good ",c)"""
    print("world")
    init1()
    readInput(a)
    initialize()
    
    #print(li_count_list)
    li_priority_list.sort()
    #print(li_priority_list)
    #solve(0)
    #print_output()
    clause_track1=clause
    lit_track={ in1 : 'none' for in1 in range(var_count)}
    #print(lit_track)
    lit_stack=deque()
    clause_no_track=[ in1 for in1 in range(clause_count) ]
    clause_var_track=[ [1 for in1 in in2 ] for in2 in clause ]
    #print(clause_var_track) 
    dpll(clause_var_track,clause_no_track,lit_stack,lit_track,deepcopy(li_count_list),deepcopy(li_list),deepcopy(lit_assigned),deepcopy(li_priority_list))



    print_output()

import sys
from collections import deque
from copy import deepcopy


if __name__=='__main__':
    main(sys.argv)