% load('phiErr.mat')
%dont forget phi error
figure(2)
lws = unique(phiErr(:,1));
angs = unique(phiErr(:,2));



phis = reshape(phiErr(:,3),[length(angs),length(lws)]);
surf(lws,angs,phis);

title('\phi(\alpha,\itl/w)');
xlabel('\itl/w');
ylabel('\alpha(\circ)');
zlabel('\phi');
figText(gcf,14);


%% plot phi vs. single angle
figure(3)
hold on;
xlabel('Angle (\circ)');
ylabel('\phi');
title('RCM Results for Symmetric Angle');

% hold on;
for(i=1:length(lws))
idx=(i-1)*13+1;

OutM=errBarCalc(angs,phis(idx:idx+12));
errorbar(OutM(:,1),OutM(:,2),OutM(:,3),'-o')
text(OutM(end,1),OutM(end,2),horzcat('\itl/w=',num2str(lws(i))));
end
axis([0,120,0.05,0.3]);
figText(gcf,14);

%%
figure(3)
[idx,val]=find(phiErr(:,2)==0.0);
LD=phiErr(idx,1);
phild = phiErr(idx,3);
phild = phild*10.5/10;
LD=14+2*14*LD
plot(LD,phild);
axis([0,140,0,.7]);

% lwTest = .9;
% angTest = 60;
% [row,~,~] = find(phiSurf(:,1)==lwTest);
% [row,~,~] = find(phiSurf(row,2)==angTest);
% val = phiSurf(row,3)
% % 
% % [~, idx] = min(abs( - 4.756));
% % pH_Mid_Pt2 = pH(idx);
% % Vb_Mid_Pt2 = Vb(idx);
% [~,idx]=min(abs(.1317-phiSurf(:,3)))
% 
% phiSurf(idx,3)
