 

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