load('phiSurf.mat')
%dont forget phi error
figure(2)
lws = unique(phiSurf(:,1));
angs = unique(phiSurf(:,2));
phis = reshape(phiSurf(:,3),[length(angs),length(lws)]);
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
