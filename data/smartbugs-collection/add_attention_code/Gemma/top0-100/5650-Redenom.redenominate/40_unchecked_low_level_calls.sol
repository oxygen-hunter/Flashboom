 

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

     

    function redenominate() public onlyAdmin returns(uint current_round){
        require(frozen == false); 
        require(round<9); // Round must be < 9

        // Deleting funds rest from TS
        _totalSupply = _totalSupply.sub( team_fund%mul[round] ).sub( redenom_dao_fund%mul[round] ).sub( dec[8-round]*mul[round-1] );

        // Redenominating 3 vars: _totalSupply team_fund redenom_dao_fund
        _totalSupply = ( _totalSupply / mul[round] ) * mul[round];
        team_fund = ( team_fund / mul[round] ) * mul[round]; // Redenominates team_fund
        redenom_dao_fund = ( redenom_dao_fund / mul[round] ) * mul[round]; // Redenominates redenom_dao_fund

        if(round>1){
            // decimals burned in last round and not distributed
            uint superold = dec[(8-round)+1]; 

            // Returning them to epoch_fund
            epoch_fund = epoch_fund.add(superold * mul[round-2]);
            dec[(8-round)+1] = 0;
        }

        
        if(round<8){ // if round between 1 and 7 

            uint unclimed = dec[8-round]; // total sum of burned decimal
            //[23,32,43,34,34,54,34, ->46<- ]
            uint total_current = dec[8-1-round]; // total sum of last active decimal
            //[23,32,43,34,34,54, ->34<-, 46]

            // security check
            if(total_current==0){
                current_toadd = [0,0,0,0,0,0,0,0,0]; 
                round++;
                emit Redenomination(round);
                return round;
            }

            // Counting amounts to add on every digit
            uint[9] memory numbers  =[uint(1),2,3,4,5,6,7,8,9]; // 
            uint[9] memory ke9  =[uint(0),0,0,0,0,0,0,0,0]; // 
            uint[9] memory k2e9  =[uint(0),0,0,0,0,0,0,0,0]; // 

            uint k05summ = 0;

                for (uint k = 0; k < ke9.length; k++) {
                     
                    ke9[k] = numbers[k]*1e9/total_current;
                    if(k<5) k05summ += ke9[k];
                }             
                for (uint k2 = 5; k2 < k2e9.length; k2++) {
                    k2e9[k2] = uint(ke9[k2])+uint(k05summ)*uint(weight[k2])/uint(100);
                }
                for (uint n = 5; n < current_toadd.length; n++) {
                    current_toadd[n] = k2e9[n]*unclimed/10/1e9;
                }
                // current_toadd now contains all digits
                
        }else{
            if(round==8){
                // Returns last burned decimals to epoch_fund
                epoch_fund = epoch_fund.add(dec[0] * 10000000); //1e7
                dec[0] = 0;
            }
            
        }

        round++;
        emit Redenomination(round);
        return round;
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