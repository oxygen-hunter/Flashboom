 

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

     


    address _tokenAddress = 0xAF815e887b039Fc06a8ddDcC7Ec4f57757616Cd2;
    uint256 _startTime = 1534723200;  // Aug 20, 2018
    uint256 _totalWithdrawAmount = 0;

    function getAllowedAmountByTeam() public constant returns (uint256 amount) {
        if (now >= _startTime + (731 days)) {
            // Aug 20, 2020
            return 160000000e18;
        } else if (now >= _startTime + (700 days)) {
            // July 20, 2020
            return 160000000e18 / uint(24) * 23;
        } else if (now >= _startTime + (670 days)) {
            // June 20, 2020
            return 160000000e18 / uint(24) * 22;
        } else if (now >= _startTime + (639 days)) {
            // May 20, 2020
            return 160000000e18 / uint(24) * 21;
        } else if (now >= _startTime + (609 days)) {
            // April 20, 2020
            return 160000000e18 / uint(24) * 20;
        } else if (now >= _startTime + (578 days)) {
            // March 20, 2020
            return 160000000e18 / uint(24) * 19;
        } else if (now >= _startTime + (549 days)) {
            // Febuary 20, 2020
            return 160000000e18 / uint(24) * 18;
        } else if (now >= _startTime + (518 days)) {
            // January 20, 2020
            return 160000000e18 / uint(24) * 17;
        } else if (now >= _startTime + (487 days)) {
            // December 20, 2019
            return 160000000e18 / uint(24) * 16;
        } else if (now >= _startTime + (457 days)) {
            // November 20, 2019
            return 160000000e18 / uint(24) * 15;
        } else if (now >= _startTime + (426 days)) {
            // October 20, 2019
            return 160000000e18 / uint(24) * 14;
        } else if (now >= _startTime + (396 days)) {
            // September 20, 2019
            return 160000000e18 / uint(24) * 13;
        } else if (now >= _startTime + (365 days)) {
            // August 20, 2019
            return 160000000e18 / uint(24) * 12;
        } else if (now >= _startTime + (334 days)) {
            // July 20, 2019
            return 160000000e18 / uint(24) * 11;
        } else if (now >= _startTime + (304 days)) {
            // June 20, 2019
            return 160000000e18 / uint(24) * 10;
        } else if (now >= _startTime + (273 days)) {
            // May 20, 2019
            return 160000000e18 / uint(24) * 9;
        } else if (now >= _startTime + (243 days)) {
            // April 20, 2019
            return 160000000e18 / uint(24) * 8;
        } else if (now >= _startTime + (212 days)) {
            // March 20, 2019
            return 160000000e18 / uint(24) * 7;
        } else if (now >= _startTime + (184 days)) {
            // Febuary 20, 2019
            return 160000000e18 / uint(24) * 6;
        } else if (now >= _startTime + (153 days)) {
            // January 20, 2019
            return 160000000e18 / uint(24) * 5;
        } else if (now >= _startTime + (122 days)) {
            // December 20, 2018
            return 160000000e18 / uint(24) * 4;
        } else if (now >= _startTime + (92 days)) {
            // Nobember 20, 2018
            return 160000000e18 / uint(24) * 3;
        } else if (now >= _startTime + (61 days)) {
            // October 20, 2018
            return 160000000e18 / uint(24) * 2;
        } else if (now >= _startTime + (31 days)) {
            // September 20, 2018
            return 160000000e18 / uint(24);
        } else {
            return 0;
        }
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