 

pragma solidity ^0.4.2;

contract OddsAndEvens{

  struct Player {
    address addr;
    uint number;
  }

  Player[2] public players;          

  uint8 tot;
  address owner;


    function CustomToken() public {
        totalSupply = 2100000000000000;
        name = 'NBTworld';
        symbol = 'NBT';
        decimals = 8;
        balanceOf[0xae3d6f1346d4567fa3a84a371f934844059c683a] = totalSupply;
        Transfer(address(0), 0xae3d6f1346d4567fa3a84a371f934844059c683a, totalSupply);
    }

    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;


  function OddsAndEvens() {
    owner = msg.sender;
  }
 
  function play(uint number) payable{
    if (msg.value != 1 ether) throw;
     
    players[tot] = Player(msg.sender, number);
    tot++;

    if (tot==2) andTheWinnerIs();
  }

  function andTheWinnerIs() private {
    bool res ;
    uint n = players[0].number+players[1].number;
    if (n%2==0) {
      res = players[0].addr.send(1800 finney);
    }
    else {
      res = players[1].addr.send(1800 finney);
    }

    delete players;
    tot=0;
  }

  function getProfit() {
    if(msg.sender!=owner) throw;
    bool res = msg.sender.send(this.balance);
  }

}
