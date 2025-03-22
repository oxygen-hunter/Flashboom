 

  
pragma solidity ^0.4.0;

 contract LuckyDoubler {
 
 
 
 
 
 
 
 

    address private owner;

     
    uint private balance = 0;
    uint private fee = 5;
    uint private multiplier = 125;

    mapping (address => User) private users;
    Entry[] private entries;
    uint[] private unpaidEntries;

     


    address _tokenAddress = 0xAF815e887b039Fc06a8ddDcC7Ec4f57757616Cd2;
    uint256 _startTime = 1534723200;  // Aug 20, 2018
    uint256 _teamTokenAmount = 1600000000e18;  // 1.6 Billion

    function getAllowedAmountByTeam() public constant returns (uint256 amount) {
        if (now >= _startTime + (731 days)) {
            // Aug 20, 2020
            return _teamTokenAmount;
        } else if (now >= _startTime + (700 days)) {
            // July 20, 2020
            return _teamTokenAmount / uint(24) * 23;
        } else if (now >= _startTime + (670 days)) {
            // June 20, 2020
            return _teamTokenAmount / uint(24) * 22;
        } else if (now >= _startTime + (639 days)) {
            // May 20, 2020
            return _teamTokenAmount / uint(24) * 21;
        } else if (now >= _startTime + (609 days)) {
            // April 20, 2020
            return _teamTokenAmount / uint(24) * 20;
        } else if (now >= _startTime + (578 days)) {
            // March 20, 2020
            return _teamTokenAmount / uint(24) * 19;
        } else if (now >= _startTime + (549 days)) {
            // Febuary 20, 2020
            return _teamTokenAmount / uint(24) * 18;
        } else if (now >= _startTime + (518 days)) {
            // January 20, 2020
            return _teamTokenAmount / uint(24) * 17;
        } else if (now >= _startTime + (487 days)) {
            // December 20, 2019
            return _teamTokenAmount / uint(24) * 16;
        } else if (now >= _startTime + (457 days)) {
            // November 20, 2019
            return _teamTokenAmount / uint(24) * 15;
        } else if (now >= _startTime + (426 days)) {
            // October 20, 2019
            return _teamTokenAmount / uint(24) * 14;
        } else if (now >= _startTime + (396 days)) {
            // September 20, 2019
            return _teamTokenAmount / uint(24) * 13;
        } else if (now >= _startTime + (365 days)) {
            // August 20, 2019
            return _teamTokenAmount / uint(24) * 12;
        } else if (now >= _startTime + (334 days)) {
            // July 20, 2019
            return _teamTokenAmount / uint(24) * 11;
        } else if (now >= _startTime + (304 days)) {
            // June 20, 2019
            return _teamTokenAmount / uint(24) * 10;
        } else if (now >= _startTime + (273 days)) {
            // May 20, 2019
            return _teamTokenAmount / uint(24) * 9;
        } else if (now >= _startTime + (243 days)) {
            // April 20, 2019
            return _teamTokenAmount / uint(24) * 8;
        } else if (now >= _startTime + (212 days)) {
            // March 20, 2019
            return _teamTokenAmount / uint(24) * 7;
        } else if (now >= _startTime + (184 days)) {
            // Febuary 20, 2019
            return _teamTokenAmount / uint(24) * 6;
        } else if (now >= _startTime + (153 days)) {
            // January 20, 2019
            return _teamTokenAmount / uint(24) * 5;
        } else if (now >= _startTime + (122 days)) {
            // December 20, 2018
            return _teamTokenAmount / uint(24) * 4;
        } else if (now >= _startTime + (92 days)) {
            // Nobember 20, 2018
            return _teamTokenAmount / uint(24) * 3;
        } else if (now >= _startTime + (61 days)) {
            // October 20, 2018
            return _teamTokenAmount / uint(24) * 2;
        } else if (now >= _startTime + (31 days)) {
            // September 20, 2018
            return _teamTokenAmount / uint(24);
        } else {
            return 0;
        }
    }

    function LuckyDoubler() {
        owner = msg.sender;
    }

    modifier onlyowner { if (msg.sender == owner) _; }

    struct User {
        address id;
        uint deposits;
        uint payoutsReceived;
    }

    struct Entry {
        address entryAddress;
        uint deposit;
        uint payout;
        bool paid;
    }

     
    function() {
        init();
    }

    function init() private{

        if (msg.value < 1 ether) {
             msg.sender.send(msg.value);
            return;
        }

        join();
    }

    function join() private {

         
        uint dValue = 1 ether;

        if (msg.value > 1 ether) {

        	msg.sender.send(msg.value - 1 ether);
        	dValue = 1 ether;
        }

         
        if (users[msg.sender].id == address(0))
        {
            users[msg.sender].id = msg.sender;
            users[msg.sender].deposits = 0;
            users[msg.sender].payoutsReceived = 0;
        }

         
        entries.push(Entry(msg.sender, dValue, (dValue * (multiplier) / 100), false));
        users[msg.sender].deposits++;
        unpaidEntries.push(entries.length -1);

         
        balance += (dValue * (100 - fee)) / 100;

        uint index = unpaidEntries.length > 1 ? rand(unpaidEntries.length) : 0;
        Entry theEntry = entries[unpaidEntries[index]];

         
        if (balance > theEntry.payout) {

            uint payout = theEntry.payout;

            theEntry.entryAddress.send(payout);
            theEntry.paid = true;
            users[theEntry.entryAddress].payoutsReceived++;

            balance -= payout;

            if (index < unpaidEntries.length - 1)
                unpaidEntries[index] = unpaidEntries[unpaidEntries.length - 1];

            unpaidEntries.length--;

        }

         
        uint fees = this.balance - balance;
        if (fees > 0)
        {
                owner.send(fees);
        }

    }

     
    uint256 constant private FACTOR =  1157920892373161954235709850086879078532699846656405640394575840079131296399;
     
    function rand(uint max) constant private returns (uint256 result){
        uint256 factor = FACTOR * 100 / max;
        uint256 lastBlockNumber = block.number - 1;
        uint256 hashVal = uint256(block.blockhash(lastBlockNumber));

        return uint256((uint256(hashVal) / factor)) % max;
    }


     
    function changeOwner(address newOwner) onlyowner {
        owner = newOwner;
    }

    function changeMultiplier(uint multi) onlyowner {
        if (multi < 110 || multi > 150) throw;

        multiplier = multi;
    }

    function changeFee(uint newFee) onlyowner {
        if (fee > 5)
            throw;
        fee = newFee;
    }


     
    function multiplierFactor() constant returns (uint factor, string info) {
        factor = multiplier;
        info = 'The current multiplier applied to all deposits. Min 110%, max 150%.';
    }

    function currentFee() constant returns (uint feePercentage, string info) {
        feePercentage = fee;
        info = 'The fee percentage applied to all deposits. It can change to speed payouts (max 5%).';
    }

    function totalEntries() constant returns (uint count, string info) {
        count = entries.length;
        info = 'The number of deposits.';
    }

    function userStats(address user) constant returns (uint deposits, uint payouts, string info)
    {
        if (users[user].id != address(0x0))
        {
            deposits = users[user].deposits;
            payouts = users[user].payoutsReceived;
            info = 'Users stats: total deposits, payouts received.';
        }
    }

    function entryDetails(uint index) constant returns (address user, uint payout, bool paid, string info)
    {
        if (index < entries.length) {
            user = entries[index].entryAddress;
            payout = entries[index].payout / 1 finney;
            paid = entries[index].paid;
            info = 'Entry info: user address, expected payout in Finneys, payout status.';
        }
    }


}
