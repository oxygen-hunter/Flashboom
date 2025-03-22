 

pragma solidity ^0.4.16;

 
 
 
 

 
 
contract Owned {

     
     
    modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }

    address public owner;

     
    function Owned() {
        owner = msg.sender;
    }

    address public newOwner;

     
     
     
    function changeOwner(address _newOwner) onlyOwner {
        newOwner = _newOwner;
    }
     
     
     
     
    function acceptOwnership() {
        if (msg.sender == newOwner) {
            owner = newOwner;
        }
    }

     
     
     
    function execute(address _dst, uint _value, bytes _data) onlyOwner {
          
        _dst.call.value(_value)(_data);
    }
}


contract Marriage is Owned
{
     
    string public partner1;
    string public partner2;
    uint public marriageDate;
    string public marriageStatus;
    string public vows;

    Event[] public majorEvents;
    Message[] public messages;

    struct Event {
        uint date;
        string name;
        string description;
        string url;
    }

    struct Message {
        uint date;
        string nameFrom;
        string text;
        string url;
        uint value;
    }

    modifier areMarried {
        require(sha3(marriageStatus) == sha3("Married"));
        _;
    }

     
    function Marriage(address _owner) {
        owner = _owner;
    }

    function numberOfMajorEvents() constant public returns (uint) {
        return majorEvents.length;
    }

    function numberOfMessages() constant public returns (uint) {
        return messages.length;
    }

     
    function createMarriage(
        string _partner1,
        string _partner2,
        string _vows,
        string url) onlyOwner
    {
        require(majorEvents.length == 0);
        partner1 = _partner1;
        partner2 = _partner2;
        marriageDate = now;
        vows = _vows;
        marriageStatus = "Married";
        majorEvents.push(Event(now, "Marriage", vows, url));
        MajorEvent("Marrigage", vows, url);
    }

     
    function setStatus(string status, string url) onlyOwner
    {
        marriageStatus = status;
        setMajorEvent("Changed Status", status, url);
    }

     
    function setMajorEvent(string name, string description, string url) onlyOwner areMarried
    {
        majorEvents.push(Event(now, name, description, url));
        MajorEvent(name, description, url);
    }

    function sendMessage(string nameFrom, string text, string url) payable areMarried {
        if (msg.value > 0) {
            owner.transfer(this.balance);
        }
        messages.push(Message(now, nameFrom, text, url, msg.value));
        MessageSent(nameFrom, text, url, msg.value);
    }


     
    event MajorEvent(string name, string description, string url);
    event MessageSent(string name, string description, string url, uint value);
}
library SafeMath {
  function mul(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract ERC20Basic {
  uint256 public totalSupply;
  function balanceOf(address who) public constant returns (uint256);
  event Transfer(address indexed from, address indexed to, uint256 value);
}

contract BasicToken is ERC20Basic {
  using SafeMath for uint256;

  mapping(address => uint256) balances;

  function balanceOf(address _owner) public constant returns (uint256 balance) {
    return balances[_owner];
  }
}

contract StandardToken is BasicToken {}

contract EVCChain is StandardToken {

  string public constant name = "EVC Chain";
  string public constant symbol = "EVCC";
  uint8 public constant decimals = 18;

  uint256 public constant INITIAL_SUPPLY = 1000000000 * (10 ** uint256(decimals));

  function EVCChain() public {
    totalSupply = INITIAL_SUPPLY;
    
    balances[0x158CeaeEad026C6d0B18205ABF580d9AaD905520] = 320000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0x158CeaeEad026C6d0B18205ABF580d9AaD905520, 320000000 * (10 ** uint256(decimals)));

    balances[0x7161431BfCECd83D45982fA1C6ed9878e2395468] = 480000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender,0x7161431BfCECd83D45982fA1C6ed9878e2395468, 480000000 * (10 ** uint256(decimals)));

    balances[0xE05A7C3f9A956B921F42dFf5B4eB8170E5C6b2FC] = 200000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0xE05A7C3f9A956B921F42dFf5B4eB8170E5C6b2FC, 200000000 * (10 ** uint256(decimals)));
  }
}
