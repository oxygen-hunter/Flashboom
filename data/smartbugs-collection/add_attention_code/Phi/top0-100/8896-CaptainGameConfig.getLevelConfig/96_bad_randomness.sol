 

pragma solidity ^0.4.25;

 
contract RandomNumberGenerator {
   
  uint256 private salt =  block.timestamp;


  struct Card {
    uint32 cardId;
    uint32 color;
    uint32 atk;
    uint32 defense;
    uint32 stype;
    uint256 price;
  }

  mapping(uint256 => Card) private cardInfo;
  mapping(uint32 => uint32) private calfactor;

  function getLevelConfig(uint32 cardId, uint32 level) external view returns (uint32 atk,uint32 defense,uint32 atk_min,uint32 atk_max) {
    if (level==1) {
      atk = cardInfo[cardId].atk;
      defense = cardInfo[cardId].defense;
    } else if (level==2) {
      atk = cardInfo[cardId].atk * 150/100;
      defense = cardInfo[cardId].defense * 150/100;
    } else if (level>=3) {
      atk = cardInfo[cardId].atk * (level-1)*2 - (level-2) * cardInfo[cardId].atk * 150/100;
      defense = cardInfo[cardId].defense * (level-1)*2 - (level-2) * cardInfo[cardId].defense * 150/100;
    }
    atk_min = calfactor[cardInfo[cardId].color]/100;
    atk_max = atk*(200-cardInfo[cardId].color)/100;
  }

  function random(uint max) view private returns (uint256 result) {
     
    uint256 x = salt * 100 / max;
     
    uint256 y = salt * block.number / (salt % 5);
     
    uint256 seed = block.number / 3 + (salt % 300) + y;
     
    uint256 h = uint256(blockhash(seed));
     
    return uint256((h / x)) % max + 1;
  }
}
