 

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
pragma solidity ^0.4.24;

contract TCallee {
    function transferFrom(address _from, address _to, uint256 _value) external returns (bool success) {}
}

contract p2ptokenexchange {
    
    struct exchange {
        address one1;
        address smart1;
        uint256 amount1;
        address two2;
        address smart2;
        uint256 amount2;
        bool DealDone;
    }
    
    mapping (uint => exchange) exchanges;
    address constant atokenaddress = 0xf0B3BA2Dd4B2ef75d727A4045d7fBcc415B77bF0;
    event DoExchange (uint exchangeId);
    
    function doExchange (uint exchangeId) external payable returns (bool success) {
        bool _locked;
        require(!_locked);
        _locked = true;
        require(msg.value >= 206000000);
        if (exchanges[exchangeId].two2 != 0x1111111111111111111111111111111111111111) {
            require(msg.sender == exchanges[exchangeId].two2);
        } else {
            exchanges[exchangeId].two2 = msg.sender;
        }
   
        require(exchanges[exchangeId].DealDone == false);
        require(exchanges[exchangeId].amount2 > 0);
       
        if (exchanges[exchangeId].smart2 == address(0)) {
            require(msg.value >= 206000000 + exchanges[exchangeId].amount2);
            require(payether(atokenaddress, msg.value - exchanges[exchangeId].amount2) == true);
        } else {
            require(payether(atokenaddress, msg.value) == true);
        }

        if (exchanges[exchangeId].smart2 == address(0)) {
            require(payether(exchanges[exchangeId].one1, exchanges[exchangeId].amount2) == true);
        } else {
            TCallee c = TCallee(exchanges[exchangeId].smart2);
            bool x = c.transferFrom(exchanges[exchangeId].two2, exchanges[exchangeId].one1, exchanges[exchangeId].amount2);
            require(x == true);
        }

        if (exchanges[exchangeId].smart1 == address(0)) {
            require(payether(exchanges[exchangeId].two2, exchanges[exchangeId].amount1) == true);
        } else {
            TCallee d = TCallee(exchanges[exchangeId].smart1);
            bool y = d.transferFrom(exchanges[exchangeId].one1, exchanges[exchangeId].two2, exchanges[exchangeId].amount1);
            require(y == true);
        }
        
        exchanges[exchangeId].DealDone = true;
        emit DoExchange(exchangeId);
        _locked = false;
        return true;
    }

    function payether(address payto, uint256 amountTo) internal returns (bool) {
        payto.transfer(amountTo);
        return true;
    }
}
