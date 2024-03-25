#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map> 
#include <limits>
#include <climits>

using namespace std;

class DiskScheduler {
public:
    // LRU
    int lru(vector<int>& requests, int initialHeadPosition) {
        int totalSeekTime = 0;
        unordered_map<int, int> cache; // Using unordered_map to simulate a cache

        for (int i = 0; i < requests.size(); ++i) {
            // Check if request is in cache
            if (cache.find(requests[i]) != cache.end()) {
                // Request found in cache, update its position
                totalSeekTime += abs(i - cache[requests[i]]);
            } else {
                // Request not found in cache, add it to cache
                totalSeekTime += abs(i - cache[requests[i]]);
                cache[requests[i]] = i; // Update cache with new request
            }
        }

        return totalSeekTime;
    }

        cache.insert(cache.begin(), initialHeadPosition);

        for (int i = 1; i < capacity; ++i) {
            totalSeekTime += abs(cache[i] - cache[i - 1]);
        }

        return totalSeekTime;
    }

    // MRU
    int mru(vector<int>& requests, int initialHeadPosition) {
        int totalSeekTime = 0;
        int capacity = requests.size();
        vector<int> cache(capacity, -1);

        for (int i = 0; i < capacity; ++i) {
            if (cache[i] == initialHeadPosition) {
                totalSeekTime += capacity - 1 - i;
                cache.erase(cache.begin() + i);
                break;
            }
        }

        cache.insert(cache.end(), initialHeadPosition);

        for (int i = 0; i < capacity - 1; ++i) {
            totalSeekTime += abs(cache[i] - cache[i + 1]);
        }

        return totalSeekTime;
    }

    // FCFS
    int fcfs(vector<int>& requests, int initialHeadPosition) {
        int totalSeekTime = 0;
        for (int i = 0; i < requests.size(); ++i) {
            totalSeekTime += abs(requests[i] - initialHeadPosition);
            initialHeadPosition = requests[i];
        }
        return totalSeekTime;
    }

    // SSTF
    // SSTF
    int sstf(vector<int>& requests, int initialHeadPosition) {
        int totalSeekTime = 0;
        vector<bool> visited(requests.size(), false);
        int n = requests.size();

        for (int i = 0; i < n; ++i) {
            int minDistance = INT_MAX; // Use INT_MAX from <climits>
            int minIndex = -1;

            for (int j = 0; j < n; ++j) {
                if (!visited[j] && abs(requests[j] - initialHeadPosition) < minDistance) {
                    minDistance = abs(requests[j] - initialHeadPosition);
                    minIndex = j;
                }
            }

            visited[minIndex] = true;
            totalSeekTime += minDistance;
            initialHeadPosition = requests[minIndex];
        }

        return totalSeekTime;
    }

    // SCAN
    int scan(vector<int>& requests, int initialHeadPosition, int totalTracks) {
        int totalSeekTime = 0;
        sort(requests.begin(), requests.end());

        auto it = lower_bound(requests.begin(), requests.end(), initialHeadPosition);
        int headIndex = distance(requests.begin(), it);

        for (int i = headIndex; i < requests.size(); ++i) {
            totalSeekTime += abs(requests[i] - initialHeadPosition);
            initialHeadPosition = requests[i];
        }

        totalSeekTime += abs(initialHeadPosition - totalTracks + 1);
        initialHeadPosition = totalTracks - 1;

        for (int i = headIndex - 1; i >= 0; --i) {
            totalSeekTime += abs(requests[i] - initialHeadPosition);
            initialHeadPosition = requests[i];
        }

        return totalSeekTime;
    }

    // C-SCAN
    int cscan(vector<int>& requests, int initialHeadPosition, int totalTracks) {
        int totalSeekTime = 0;
        sort(requests.begin(), requests.end());

        auto it = lower_bound(requests.begin(), requests.end(), initialHeadPosition);
        int headIndex = distance(requests.begin(), it);

        for (int i = headIndex; i < requests.size(); ++i) {
            totalSeekTime += abs(requests[i] - initialHeadPosition);
            initialHeadPosition = requests[i];
        }

        totalSeekTime += abs(initialHeadPosition - totalTracks + 1);
        initialHeadPosition = 0;

        for (int i = 0; i < headIndex; ++i) {
            totalSeekTime += abs(requests[i] - initialHeadPosition);
            initialHeadPosition = requests[i];
        }

        return totalSeekTime;
    }

    // C-LOOK
    int clook(vector<int>& requests, int initialHeadPosition) {
        int totalSeekTime = 0;
        sort(requests.begin(), requests.end());

        auto it = lower_bound(requests.begin(), requests.end(), initialHeadPosition);
        int headIndex = distance(requests.begin(), it);

        for (int i = headIndex; i < requests.size(); ++i) {
            totalSeekTime += abs(requests[i] - initialHeadPosition);
            initialHeadPosition = requests[i];
        }

        for (int i = 0; i < headIndex; ++i) {
            totalSeekTime += abs(requests[i] - initialHeadPosition);
            initialHeadPosition = requests[i];
        }

        return totalSeekTime;
    }

        // LOOK
    int look(vector<int>& requests, int initialHeadPosition) {
        int totalSeekTime = 0;
        sort(requests.begin(), requests.end());

        auto it = lower_bound(requests.begin(), requests.end(), initialHeadPosition);
        int headIndex = distance(requests.begin(), it);

        for (int i = headIndex; i < requests.size(); ++i) {
            totalSeekTime += abs(requests[i] - initialHeadPosition);
            initialHeadPosition = requests[i];
        }

        for (int i = headIndex - 1; i >= 0; --i) {
            totalSeekTime += abs(requests[i] - initialHeadPosition);
            initialHeadPosition = requests[i];
        }

        return totalSeekTime;
    }
};

int main() {
    DiskScheduler scheduler;
    vector<int> requests;
    int initialHeadPosition;
    int totalTracks;
    int choice;

    cout << "Enter the number of disk requests: ";
    int numRequests;
    cin >> numRequests;

    cout << "Enter the disk requests: ";
    for (int i = 0; i < numRequests; ++i) {
        int request;
        cin >> request;
        requests.push_back(request);
    }

    cout << "Enter the initial head position: ";
    cin >> initialHeadPosition;

    cout << "Enter the total number of tracks on the disk: ";
    cin >> totalTracks;

    cout << "Choose the disk scheduling algorithm:" << endl;
    cout << "1. LRU" << endl;
    cout << "2. MRU" << endl;
    cout << "3. FCFS" << endl;
    cout << "4. SSTF" << endl;
    cout << "5. SCAN" << endl;
    cout << "6. C-SCAN" << endl;
    cout << "7. C-LOOK" << endl;
    cout << "8. LOOK" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    int totalSeekTime;
    switch (choice) {
        case 1:
            totalSeekTime = scheduler.lru(requests, initialHeadPosition);
            break;
        case 2:
            totalSeekTime = scheduler.mru(requests, initialHeadPosition);
            break;
        case 3:
            totalSeekTime = scheduler.fcfs(requests, initialHeadPosition);
            break;
        case 4:
            totalSeekTime = scheduler.sstf(requests, initialHeadPosition);
            break;
        case 5:
            totalSeekTime = scheduler.scan(requests, initialHeadPosition, totalTracks);
            break;
        case 6:
            totalSeekTime = scheduler.cscan(requests, initialHeadPosition, totalTracks);
            break;
        case 7:
            totalSeekTime = scheduler.clook(requests, initialHeadPosition);
            break;
        case 8:
            totalSeekTime = scheduler.look(requests, initialHeadPosition);
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }

    cout << "Total Seek Time: " << totalSeekTime << endl;

    return 0;
}

