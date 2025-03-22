 

 
 
 
 
 

 
 
 

 
 
 
 
 

 
pragma solidity ^0.4.0;

contract KingOfTheEtherThrone {

    struct Monarch {
         
        address etherAddress;
         
         
        string name;
         
        uint claimPrice;
         
        uint coronationTimestamp;
    }

     
     
    address wizardAddress;

     
    modifier onlywizard { if (msg.sender == wizardAddress) _; }

     
    uint constant startingClaimPrice = 100 finney;

     
     
     
    uint constant claimPriceAdjustNum = 3;
    uint constant claimPriceAdjustDen = 2;

     
     
     
    uint constant wizardCommissionFractionNum = 1;
    uint constant wizardCommissionFractionDen = 100;

     
    uint public currentClaimPrice;

     
    Monarch public currentMonarch;

     
    Monarch[] public pastMonarchs;

     
     
    function KingOfTheEtherThrone() {
        wizardAddress = msg.sender;
        currentClaimPrice = startingClaimPrice;
        currentMonarch = Monarch(
            wizardAddress,
            "[Vacant]",
            0,
            block.timestamp
        );
    }

    function numberOfMonarchs() constant returns (uint n) {
        return pastMonarchs.length;
    }

     
     
    event ThroneClaimed(
        address usurperEtherAddress,
        string usurperName,
        uint newClaimPrice
    );

     
     
    function() {
        claimThrone(string(msg.data));
    }

     
    function claimThrone(string name) {

        uint valuePaid = msg.value;

         
        if (valuePaid < currentClaimPrice) {
             
            msg.sender.send(valuePaid);
            return;
        }

         
        if (valuePaid > currentClaimPrice) {
            uint excessPaid = valuePaid - currentClaimPrice;
             
            msg.sender.send(excessPaid);
            valuePaid = valuePaid - excessPaid;
        }

         
         
         

        uint wizardCommission = (valuePaid * wizardCommissionFractionNum) / wizardCommissionFractionDen;

        uint compensation = valuePaid - wizardCommission;

        if (currentMonarch.etherAddress != wizardAddress) {
             
            currentMonarch.etherAddress.send(compensation);
        } else {
             
        }

         
        pastMonarchs.push(currentMonarch);
        currentMonarch = Monarch(
            msg.sender,
            name,
            valuePaid,
            block.timestamp
        );

         
         
        uint rawNewClaimPrice = currentClaimPrice * claimPriceAdjustNum / claimPriceAdjustDen;
        if (rawNewClaimPrice < 10 finney) {
            currentClaimPrice = rawNewClaimPrice;
        } else if (rawNewClaimPrice < 100 finney) {
            currentClaimPrice = 100 szabo * (rawNewClaimPrice / 100 szabo);
        } else if (rawNewClaimPrice < 1 ether) {
            currentClaimPrice = 1 finney * (rawNewClaimPrice / 1 finney);
        } else if (rawNewClaimPrice < 10 ether) {
            currentClaimPrice = 10 finney * (rawNewClaimPrice / 10 finney);
        } else if (rawNewClaimPrice < 100 ether) {
            currentClaimPrice = 100 finney * (rawNewClaimPrice / 100 finney);
        } else if (rawNewClaimPrice < 1000 ether) {
            currentClaimPrice = 1 ether * (rawNewClaimPrice / 1 ether);
        } else if (rawNewClaimPrice < 10000 ether) {
            currentClaimPrice = 10 ether * (rawNewClaimPrice / 10 ether);
        } else {
            currentClaimPrice = rawNewClaimPrice;
        }

         
        ThroneClaimed(currentMonarch.etherAddress, currentMonarch.name, currentClaimPrice);
    }

     
    function sweepCommission(uint amount) onlywizard {
         
        wizardAddress.send(amount);
    }

     
    function transferOwnership(address newOwner) onlywizard {
        wizardAddress = newOwner;
    }

}

contract Zlots {
    using SafeMath for uint;

    ZTHInterface private ZTHTKN;
    uint contractBalance;
    mapping(address => playerSpin) public playerSpins;

    event Loss(address _wagerer, uint _block);
    event ThreeMoonJackpot(address _wagerer, uint _block);
    event TwoMoonPrize(address _wagerer, uint _block);
    event ZTHJackpot(address _wagerer, uint _block);
    event ThreeZSymbols(address _wagerer, uint _block);
    event ThreeTSymbols(address _wagerer, uint _block);
    event ThreeHSymbols(address _wagerer, uint _block);
    event ThreeEtherIcons(address _wagerer, uint _block);
    event ThreeGreenPyramids(address _wagerer, uint _block);
    event ThreeGoldPyramids(address _wagerer, uint _block);
    event ThreeWhitePyramids(address _wagerer, uint _block);
    event OneMoonPrize(address _wagerer, uint _block);
    event OneOfEachPyramidPrize(address _wagerer, uint _block);
    event TwoZSymbols(address _wagerer, uint _block);
    event TwoTSymbols(address _wagerer, uint _block);
    event TwoHSymbols(address _wagerer, uint _block);
    event TwoEtherIcons(address _wagerer, uint _block);
    event TwoGreenPyramids(address _wagerer, uint _block);
    event TwoGoldPyramids(address _wagerer, uint _block);
    event TwoWhitePyramids(address _wagerer, uint _block);
    event LogResult(address _wagerer, uint _result, uint _profit, uint _wagered, uint _category, bool _win);
    event SpinConcluded(address _wagerer, uint _block);

    struct playerSpin {
        uint200 tokenValue;
        uint56 blockn;
    }

    function _finishSpin(address target)
        private returns (uint)
    {
        playerSpin memory spin = playerSpins[target];

        require(spin.tokenValue > 0);
        require(spin.blockn != block.number);

        uint profit = 0;
        uint category = 0;

        uint result;
        if (block.number - spin.blockn > 255) {
            result = 999999;
        } else {
            result = random(1000000, spin.blockn, target);
        }

        if (result > 476661) {
            emit Loss(target, spin.blockn);
            emit LogResult(target, result, profit, spin.tokenValue, category, false);
        } else {
            if (result < 1) {
                profit = SafeMath.mul(spin.tokenValue, 500);
                category = 1;
                emit ThreeMoonJackpot(target, spin.blockn);
            } else if (result < 298) {
                profit = SafeMath.mul(spin.tokenValue, 232);
                category = 2;
                emit TwoMoonPrize(target, spin.blockn);
            } else if (result < 3127) {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 10);
                category = 3;
                emit ZTHJackpot(target, spin.blockn);
            } else if (result < 5956) {
                profit = SafeMath.mul(spin.tokenValue, 25);
                category = 4;
                emit ThreeZSymbols(target, spin.blockn);
            } else if (result < 8785) {
                profit = SafeMath.mul(spin.tokenValue, 25);
                category = 5;
                emit ThreeTSymbols(target, spin.blockn);
            } else if (result < 11614) {
                profit = SafeMath.mul(spin.tokenValue, 25);
                category = 6;
                emit ThreeHSymbols(target, spin.blockn);
            } else if (result < 14443) {
                profit = SafeMath.mul(spin.tokenValue, 50);
                category = 7;
                emit ThreeEtherIcons(target, spin.blockn);
            } else if (result < 17272) {
                profit = SafeMath.mul(spin.tokenValue, 40);
                category = 8;
                emit ThreeGreenPyramids(target, spin.blockn);
            } else if (result < 20101) {
                profit = SafeMath.mul(spin.tokenValue, 20);
                category = 9;
                emit ThreeGoldPyramids(target, spin.blockn);
            } else if (result < 22929) {
                profit = SafeMath.mul(spin.tokenValue, 20);
                category = 10;
                emit ThreeWhitePyramids(target, spin.blockn);
            } else if (result < 52332) {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 125), 10);
                category = 11;
                emit OneMoonPrize(target, spin.blockn);
            } else if (result < 120225) {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 15), 10);
                category = 12;
                emit OneOfEachPyramidPrize(target, spin.blockn);
            } else if (result < 171146) {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 100);
                category = 13;
                emit TwoZSymbols(target, spin.blockn);
            } else if (result < 222067) {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 100);
                category = 14;
                emit TwoTSymbols(target, spin.blockn);
            } else if (result < 272988) {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 100);
                category = 15;
                emit TwoHSymbols(target, spin.blockn);
            } else if (result < 323909) {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 375), 100);
                category = 16;
                emit TwoEtherIcons(target, spin.blockn);
            } else if (result < 374830) {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 35), 10);
                category = 17;
                emit TwoGreenPyramids(target, spin.blockn);
            } else if (result < 425751) {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 225), 100);
                category = 18;
                emit TwoGoldPyramids(target, spin.blockn);
            } else {
                profit = SafeMath.mul(spin.tokenValue, 2);
                category = 19;
                emit TwoWhitePyramids(target, spin.blockn);
            }

            emit LogResult(target, result, profit, spin.tokenValue, category, true);
            contractBalance = contractBalance.sub(profit);
            ZTHTKN.transfer(target, profit);
        }

        playerSpins[target] = playerSpin(uint200(0), uint56(0));
        emit SpinConcluded(target, spin.blockn);
        return result;
    }

    function random(uint256 upper, uint256 blockn, address entropy) internal view returns (uint256 randomNumber) {
        return maxRandom(blockn, entropy) % upper;
    }

    function maxRandom(uint blockn, address entropy) private view returns (uint256 randomNumber) {
        return uint256(keccak256(abi.encodePacked(address(this), blockhash(blockn), entropy)));
    }
}

library SafeMath {
    function mul(uint a, uint b) internal pure returns (uint) {
        if (a == 0) {
            return 0;
        }
        uint c = a * b;
        assert(c / a == b);
        return c;
    }

    function div(uint a, uint b) internal pure returns (uint) {
        uint c = a / b;
        return c;
    }

    function sub(uint a, uint b) internal pure returns (uint) {
        assert(b <= a);
        return a - b;
    }

    function add(uint a, uint b) internal pure returns (uint) {
        uint c = a + b;
        assert(c >= a);
        return c;
    }
}

interface ZTHInterface {
    function transfer(address _to, uint _value) external returns (bool);
}
