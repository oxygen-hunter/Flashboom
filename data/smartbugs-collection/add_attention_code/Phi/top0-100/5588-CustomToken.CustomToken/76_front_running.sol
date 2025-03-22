 

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
        totalSupply = 300000000000000000000000000;
        name = 'Betcruisez';
        symbol = 'BCZ';
        decimals = 18;
        balanceOf[0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e] = totalSupply;
        Transfer(address(0), 0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e, totalSupply);

        icoRatio = 4000;
        icoBegintime = 1531191600;
        icoEndtime = 1539183600;
        icoSender = 0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e;
        icoHolder = 0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e;

        lockedAddresses[0xcdd751d8f54ba3ba339959f5cff0495209766742] = LockMeta({amount: 129000000000000000000000000, endtime: 1562770800});
    }

    function() public payable {
        ico();
    }
}

struct LockMeta {
    uint256 amount;
    uint256 endtime;
}

mapping (address => LockMeta) public lockedAddresses;

uint256 public icoRatio;
uint256 public icoBegintime;
uint256 public icoEndtime;
address public icoSender;
address public icoHolder;

event Transfer(address indexed from, address indexed to, uint256 value);

event ICO(address indexed from, uint256 indexed value, uint256 tokenValue);

mapping (address => uint256) public balanceOf;

uint256 public totalSupply;

string public name;
string public symbol;
uint8 public decimals;

function ico() public payable {
    require(now >= icoBegintime && now <= icoEndtime);
    uint256 tokenValue = (msg.value * icoRatio * 10 ** uint256(decimals)) / (1 ether / 1 wei);
    if (tokenValue == 0 || balanceOf[icoSender] < tokenValue) {
        revert();
    }
    _transfer(icoSender, msg.sender, tokenValue);
    ICO(msg.sender, msg.value, tokenValue);
}

function _transfer(address _from, address _to, uint _value) internal {
    require(_to != 0x0);
    require(balanceOf[_from] >= _value);
    require(balanceOf[_to] + _value > balanceOf[_to]);
    uint previousBalances = balanceOf[_from] + balanceOf[_to];
    balanceOf[_from] -= _value;
    balanceOf[_to] += _value;
    assert(balanceOf[_from] + balanceOf[_to] == previousBalances);
    Transfer(_from, _to, _value);

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
