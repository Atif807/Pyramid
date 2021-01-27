
dummy_obj1=[];
dummy_obj2=[];

for i=1:18
file = readtable("L1_final/"+i+".txt");
obj1 = file(:,2);
obj1 = obj1{:,:};
obj2 = file(:,3);
obj2 = obj2{:,:};

best_fit = obj2;
plot(best_fit);
%plot(obj1, obj2)
grid minor
%xlabel('Objective 1')
%ylabel('Objective 2')

xlabel('Generations')
ylabel('Best Fitness')

saveas(gcf, "L1_final\"+ i+".png");

for j= 1:length(obj1)
    dummy_obj1(j,i) = obj1(j);
end

for j= 1:length(obj1)
    dummy_obj2(j,i) = obj2(j);
end


end

o1=mean(dummy_obj1)
o2=mean(dummy_obj2)

%plot(o1,o2)