[sx1,sy1,sz1]=sphere(100);
% sx1=sx1*dim/2;
% sy1=sy1*dim/2;
% sz1=sz1*dim/2;
c = [4,4,4] %sphere center
mesh(sx1+c(1),sy1+c(2),sz1+c(3),'FaceAlpha',.4);
hold on;
xlabel('x');
ylabel('y');
zlabel('z');
axis equal;
% axis([0,dim+D,0,dim+D,0,dim+D]);

%% random distrib inside sphere
for(i=1:200)
a=6*rand(1,3)-3;
u=rand(1,1);
a=a/norm(a);
a=a*u^(1/3)+c;

plot3(a(1),a(2),a(3),'*b');
end
%% random distrib on sphere

for(i=1:1000)
a=2*rand(1,3)-1;
a=a/norm(a);
a=a+c;

plot3(a(1),a(2),a(3),'*');
end