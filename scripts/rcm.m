function [lw, phi,ang1,ang2]= rcm(fold,C) 
%C=contact number from paper

% C = 10.5;
% pars = '0.2-90-90-122\';
% fold = 'D:\RCMcode\RCM\Results\UShape\';
PON=0;
% points1     = importdata(horzcat(fold,pars,'mainStaple.txt'));
% points2     = importdata(horzcat(fold,pars,'secondStaple.txt'));
% intersects  = importdata(horzcat(fold,pars,'intersects.txt'));
% res         = importdata(horzcat(fold,pars,'results.txt'));

if PON==1
    points1     = importdata(horzcat(fold,'mainStaple.txt'));
    points2     = importdata(horzcat(fold,'secondStaple.txt'));
    intersects  = importdata(horzcat(fold,'intersects.txt'));
end
res         = importdata(horzcat(fold,'results.txt'));


its= res(1);
completed = res(2);
nonCols=res(3);
D=res(4);
L=res(5);
W=res(6);
dim=res(7); %diam
ang1=res(8);
ang2=res(9);

vp  = pi*(W)*(D/2)^2+2*pi*L*(D/2)^2+4/3*pi*(D/2)^3;

% vp2 = pi/6*D^3*(3-1) + pi/4*D^2*(W+2*L);
if L==0
    vp=pi/6*D^3 + pi/4*D^2*(W+2*L);
end
% p=(nonCols)/completed;
p=(completed-nonCols)/completed;

V=4/3*pi*((dim)/2)^3;

% phi=[10.8*vp/(p*V) 10.8*vp2/(p*V)]
phi=C*vp/(p*V);
% pts('p:',p,'  p*V:', p*V);
loops=600;
% F(loops) = struct('cdata',[],'colormap',[]);
% close all
if PON
    [sx,sy,sz]=sphere(100);
    sx=dim/2*sx+dim/2;
    sy=dim/2*sy+dim/2;
    sz=dim/2*sz+dim/2;
    staples(1)= struct('c1',zeros(3,2),'c2',zeros(3,2),'c3',zeros(3,2));
    for (i=1:size(points2,1)/6)
        staples(i).c1=points2(6*(i-1)+1:6*(i-1)+2,:)';
        staples(i).c2=points2(6*(i-1)+3:6*(i-1)+4,:)';
        staples(i).c3=points2(6*(i-1)+5:6*(i-1)+6,:)';
    end

%     mainStaple = struct('c1',points1(1:2,:)','c2',points1(3:4,:)','c3',points1(5:6,:)');
    mainStaples= struct('c1',zeros(3,2),'c2',zeros(3,2),'c3',zeros(3,2));
    for (i=1:size(points1,1)/6)
        mainStaples(i).c1=points1(6*(i-1)+1:6*(i-1)+2,:)';
        mainStaples(i).c2=points1(6*(i-1)+3:6*(i-1)+4,:)';
        mainStaples(i).c3=points1(6*(i-1)+5:6*(i-1)+6,:)';
    end

    mainCol = [1,0,0]';
    otherCol= [0,0,1]';
    mesh(sx,sy,sz,'FaceAlpha',.4);
for(i=1:loops)
    hold on;
    plot3(1,1,1);
%     tubeplot(mainStaple.c1,D/2,20,mainCol);
%     hold on;
%     
% %     mesh(sx,sy,sz,'FaceAlpha',.4);
%     
%     tubeplot(mainStaple.c2,D/2,20,mainCol);
%     tubeplot(mainStaple.c3,D/2,20,mainCol);
    
    tubeplot(mainStaples(i).c1,D/2,20,mainCol);
    hold on;
    tubeplot(mainStaples(i).c2,D/2,20,mainCol);
    tubeplot(mainStaples(i).c3,D/2,20,mainCol);

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
	drawnow;
%     F(i) = getframe(gcf);
%    pause;
    %close all
    end
end
lw = L/W;
% totalPhi(s+1,:)=[(L-D)/(W-D), phi]
