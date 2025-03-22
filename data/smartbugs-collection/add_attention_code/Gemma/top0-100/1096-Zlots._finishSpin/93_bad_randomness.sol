 

  
pragma solidity ^0.4.0;

 contract LuckyDoubler {
 
 
 
 
 
 
 
 

    address private owner;

     
    uint private balance = 0;
    uint private fee = 5;
    uint private multiplier = 125;

    mapping (address => User) private users;
    Entry[] private entries;
    uint[] private unpaidEntries;

     

    function _finishSpin(address target)
        private returns (uint)
    {
        playerSpin memory spin = playerSpins[target];

        require(spin.tokenValue > 0); // No re-entrancy
        require(spin.blockn != block.number);

        uint profit = 0;
        uint category = 0;

        // If the block is more than 255 blocks old, we can't get the result
        // Also, if the result has already happened, fail as well
        uint result;
        if (block.number - spin.blockn > 255) {
          result = 1000000; // Can't win: default to largest number
        } else {

          // Generate a result - random based ONLY on a past block (future when submitted).
          // Case statement barrier numbers defined by the current payment schema at the top of the contract.
          result = random(1000000, spin.blockn, target) + 1;
        }

        if (result > 476662) {
            // Player has lost. Womp womp.

            // Add one percent of player loss to the jackpot
            // (do this by requesting a payout to the jackpot)
            RequestBankrollPayment(zlotsJackpot, profit, tier);

            // Null out player spin
            playerSpins[target] = playerSpin(uint200(0), uint48(0), uint8(0));

            emit Loss(target, spin.blockn);
            emit LogResult(target, result, profit, spin.tokenValue, category, false);
        } else if (result < 2) {
            // Player has won the three-moon mega jackpot!
      
            // Get profit amount via jackpot
            profit = ZlotsJackpotHoldingContract(zlotsJackpot).getJackpot();
            category = 1;
    
            // Emit events
            emit ThreeMoonJackpot(target, spin.blockn);
            emit LogResult(target, result, profit, spin.tokenValue, category, true);

            // Grab the tier
            uint8 tier = spin.tier;

            // Null out spins
            playerSpins[target] = playerSpin(uint200(0), uint48(0), uint8(0));

            // Pay out the winner
            ZlotsJackpotHoldingContract(zlotsJackpot).payOutWinner(target);
        } else {
            if (result < 299) {
                // Player has won a two-moon prize!
                profit = SafeMath.mul(spin.tokenValue, 100);
                category = 2;
                emit TwoMoonPrize(target, spin.blockn);
            } else if (result < 3128) {
                // Player has won the Z T H prize!
                profit = SafeMath.mul(spin.tokenValue, 20);
                category = 3;
                emit ZTHPrize(target, spin.blockn);
            } else if (result < 5957) {
                // Player has won a three Z symbol prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 75), 10);
                category = 4;
                emit ThreeZSymbols(target, spin.blockn);
            } else if (result < 8786) {
                // Player has won a three T symbol prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 75), 10);
                category = 5;
                emit ThreeTSymbols(target, spin.blockn);
            } else if (result < 11615) {
                // Player has won a three H symbol prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 75), 10);
                category = 6;
                emit ThreeHSymbols(target, spin.blockn);
            } else if (result < 14444) {
                // Player has won a three Ether icon prize!
                profit = SafeMath.mul(spin.tokenValue, 15);
                category = 7;
                emit ThreeEtherIcons(target, spin.blockn);
            } else if (result < 17273) {
                // Player has won a three purple pyramid prize!
                profit = SafeMath.mul(spin.tokenValue, 10);
                category = 8;
                emit ThreePurplePyramids(target, spin.blockn);
            } else if (result < 20102) {
                // Player has won a three gold pyramid prize!
                profit = SafeMath.mul(spin.tokenValue, 10);
                category = 9;
                emit ThreeGoldPyramids(target, spin.blockn);
            } else if (result < 22930) {
                // Player has won a three rocket prize!
                profit = SafeMath.mul(spin.tokenValue, 12);
                category = 10;
                emit ThreeRockets(target, spin.blockn);
            } else if (result < 52333) {
                // Player has won a one moon prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 25),10);
                category = 11;
                emit OneMoonPrize(target, spin.blockn);
            } else if (result < 120226) {
                // Player has won a each-coloured-pyramid prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 15),10);
                category = 12;
                emit OneOfEachPyramidPrize(target, spin.blockn);
            } else if (result < 171147) {
                // Player has won a two Z symbol prize!
                profit = spin.tokenValue;
                category = 13;
                 emit TwoZSymbols(target, spin.blockn);
            } else if (result < 222068) {
                // Player has won a two T symbol prize!
                profit = spin.tokenValue;
                category = 14;
                emit TwoTSymbols(target, spin.blockn);
            } else if (result < 272989) {
                // Player has won a two H symbol prize!
                profit = spin.tokenValue;
                category = 15;
                emit TwoHSymbols(target, spin.blockn);
            } else if (result < 323910) {
                // Player has won a two Ether icon prize!
                profit = SafeMath.mul(spin.tokenValue, 2);
                category = 16;
                emit TwoEtherIcons(target, spin.blockn);
            } else if (result < 374831) {
                // Player has won a two purple pyramid prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 133),100);
                category = 17;
                emit TwoPurplePyramids(target, spin.blockn);
            } else if (result < 425752) {
                // Player has won a two gold pyramid prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 133),100);
                category = 18;
                emit TwoGoldPyramids(target, spin.blockn);
            } else {
                // Player has won a two rocket prize!
                profit = SafeMath.mul(spin.tokenValue, 2);
                category = 19;
                emit TwoRockets(target, spin.blockn);
            }

            emit LogResult(target, result, profit, spin.tokenValue, category, true);
            tier = spin.tier;
            playerSpins[target] = playerSpin(uint200(0), uint48(0), uint8(0)); // Prevent Re-entrancy
            RequestBankrollPayment(target, profit, tier);
          }
            
        emit SpinConcluded(target, spin.blockn);
        return result;
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
