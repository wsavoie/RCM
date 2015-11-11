% ang1 = 120;
% ang2 = 120;
% 
% system(horzcat('D:\GeometryCode\GTEngine\Executable\v120\Win32\Release\_Output\v120\Win32\Release\CapsuleIntersect.v12.exe'...
%     ,' ',num2str(ang1),' ',num2str(ang2)))
% !D:\GeometryCode\GTEngine\Executable\v120\Win32\Release\_Output\v120\Win32\Release\CapsuleIntersect.v12.exe 120 120 &

PON=1;
points1 = importdata('D:\RCMcode\RCM\Release\mainStaple.txt');
points2 = importdata('D:\RCMcode\RCM\Release\secondStaple.txt');
intersects = importdata('D:\RCMcode\RCM\Release\intersects.txt');
res = importdata('D:\RCMcode\RCM\Release\results.txt');
its= res(1);
completed = res(2);
nonCols=res(3);
D=res(4);
L=res(5);
W=res(6);
dim=res(7);
vp = pi*W*(D/2)^2+2*pi*L*(D/2)^2+4/3*pi*(D/2)^3;
p=(completed-nonCols)/completed;
p2=(nonCols)/completed;

V=4/3*pi*(dim/2)^3;
V2=(dim^3);


phi=[10*vp/(p*V) 10*vp/(p*V2) 10*vp/(p2*V) 10*vp/(p2*V2)]

close all
if PON
    [sx,sy,sz]=sphere(100);
    sx=dim/2*sx+dim/2;
    sy=dim/2*sy+dim/2;
    sz=dim/2*sz+dim/2;
    staples(1)= struct('c1',zeros(3,2),'c2',zeros(3,2),'c3',zeros(3,2));
    for (i=1:size(points2,1)/6)
        staples(i).c2=points2(6*(i-1)+1:6*(i-1)+2,:)';
        staples(i).c3=points2(6*(i-1)+3:6*(i-1)+4,:)';
        staples(i).c1=points2(6*(i-1)+5:6*(i-1)+6,:)';
    end

    mainStaple = struct('c1',points1(1:2,:)','c2',points1(3:4,:)','c3',points1(5:6,:)');

    mainCol = [1,0,0]';
    otherCol= [0,0,1]';
    for(i=1:50)
    hold off;
    plot3(1,1,1);
    tubeplot(mainStaple.c1,D/2,20,mainCol);
    hold on;
    
    mesh(sx,sy,sz,'FaceAlpha',.4);
    
    tubeplot(mainStaple.c2,D/2,20,mainCol);
    tubeplot(mainStaple.c3,D/2,20,mainCol);

    %plot second staple
    if intersects(i)
        otherCol = [0,0,1]';
    else
        otherCol = [0,1,0]';
    end
    tubeplot(staples(i).c1,D/2,20,otherCol);
    tubeplot(staples(i).c2,D/2,20,otherCol);
    tubeplot(staples(i).c3,D/2,20,otherCol);
    xlabel('x');
    ylabel('y');
    zlabel('z');
    axis equal;
    axis([0,dim+D,0,dim+D,0,dim+D]);
     pause();
   % pause;
    %close all
    end
end