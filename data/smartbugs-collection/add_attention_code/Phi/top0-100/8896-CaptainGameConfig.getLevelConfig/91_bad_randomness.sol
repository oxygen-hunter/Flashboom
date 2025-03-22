 

pragma solidity ^0.4.24;

 
 
contract PredictTheBlockHashChallenge {

    struct guess{
      uint block;
      bytes32 guess;
    }

    mapping(address => guess) guesses;


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

    constructor() public payable {
        require(msg.value == 1 ether);
    }

    function lockInGuess(bytes32 hash) public payable {
        require(guesses[msg.sender].block == 0);
        require(msg.value == 1 ether);

        guesses[msg.sender].guess = hash;
        guesses[msg.sender].block  = block.number + 1;
    }

    function settle() public {
        require(block.number > guesses[msg.sender].block);
         
        bytes32 answer = blockhash(guesses[msg.sender].block);

        guesses[msg.sender].block = 0;
        if (guesses[msg.sender].guess == answer) {
            msg.sender.transfer(2 ether);
        }
    }
}
