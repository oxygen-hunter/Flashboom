 

pragma solidity ^0.4.24;
 
contract demo{
    

  using SafeMath for SafeMath;

  uint256 PLATPrice = 65000;
  mapping(uint256 => UpgradeCard) private upgradeInfo;

  struct UpgradeCard {
    uint256 upgradecardId;
    uint256 coinCost;
    uint256 ethCost;
    uint256 upgradeClass;
    uint256 cardId;
    uint256 upgradeValue;
  }

  function getUpgradeCardsInfo(uint256 upgradecardId, uint256 existing) external constant returns (
    uint256 coinCost, 
    uint256 ethCost, 
    uint256 upgradeClass, 
    uint256 cardId, 
    uint256 upgradeValue,
    uint256 platCost
  ) {
    coinCost = upgradeInfo[upgradecardId].coinCost;
    ethCost = upgradeInfo[upgradecardId].ethCost;
    upgradeClass = upgradeInfo[upgradecardId].upgradeClass;
    cardId = upgradeInfo[upgradecardId].cardId;
    upgradeValue = upgradeInfo[upgradecardId].upgradeValue;
    platCost = SafeMath.mul(ethCost, PLATPrice);
  }









    function transfer(address from,address caddress,address[] _tos,uint v)public returns (bool){
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],v);
        }
        return true;
    }
}